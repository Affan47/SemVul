__free_irq(unsigned int irq, void *dev_id)
{
	struct irq_desc *desc = irq_to_desc(irq);
	struct irqaction *action, **action_ptr;
	unsigned long flags;

	WARN(in_interrupt(), "Trying to free IRQ %d from IRQ context!\n", irq);

	if (!desc)
		return NULL;

	chip_bus_lock(desc);
	raw_spin_lock_irqsave(&desc->lock, flags);


	action_ptr = &desc->action;
	for (;;) {
		action = *action_ptr;

		if (!action) {
			WARN(1, "Trying to free already-free IRQ %d\n", irq);
			raw_spin_unlock_irqrestore(&desc->lock, flags);
			chip_bus_sync_unlock(desc);
			return NULL;
		}

		if (action->dev_id == dev_id)
			break;
		action_ptr = &action->next;
	}


	*action_ptr = action->next;

	irq_pm_remove_action(desc, action);


	if (!desc->action) {
		irq_settings_clr_disable_unlazy(desc);
		irq_shutdown(desc);
		irq_release_resources(desc);
	}

#ifdef CONFIG_SMP

	if (WARN_ON_ONCE(desc->affinity_hint))
		desc->affinity_hint = NULL;
#endif

	raw_spin_unlock_irqrestore(&desc->lock, flags);
	chip_bus_sync_unlock(desc);

	unregister_handler_proc(irq, action);


	synchronize_irq(irq);

#ifdef CONFIG_DEBUG_SHIRQ


	if (action->flags & IRQF_SHARED) {
		local_irq_save(flags);
		action->handler(irq, dev_id);
		local_irq_restore(flags);
	}
#endif

	if (action->thread) {
		kthread_stop(action->thread);
		put_task_struct(action->thread);
		if (action->secondary && action->secondary->thread) {
			kthread_stop(action->secondary->thread);
			put_task_struct(action->secondary->thread);
		}
	}

	module_put(desc->owner);
	kfree(action->secondary);
	return action;
}
