freeary(struct ipc_namespace *ns, struct kern_ipc_perm *ipcp)
{
	struct sem_undo *un, *tu;
	struct sem_queue *q, *tq;
	struct sem_array *sma = container_of(ipcp, struct sem_array, sem_perm);
	struct list_head tasks;
	int i;


	ipc_assert_locked_object(&sma->sem_perm);
	list_for_each_entry_safe(un, tu, &sma->list_id, list_id) {
		list_del(&un->list_id);
		spin_lock(&un->ulp->lock);
		un->semid = -1;
		list_del_rcu(&un->list_proc);
		spin_unlock(&un->ulp->lock);
		kfree_rcu(un, rcu);
	}


	INIT_LIST_HEAD(&tasks);
	list_for_each_entry_safe(q, tq, &sma->pending_const, list) {
		unlink_queue(sma, q);
		wake_up_sem_queue_prepare(&tasks, q, -EIDRM);
	}

	list_for_each_entry_safe(q, tq, &sma->pending_alter, list) {
		unlink_queue(sma, q);
		wake_up_sem_queue_prepare(&tasks, q, -EIDRM);
	}
	for (i = 0; i < sma->sem_nsems; i++) {
		struct sem *sem = sma->sem_base + i;
		list_for_each_entry_safe(q, tq, &sem->pending_const, list) {
			unlink_queue(sma, q);
			wake_up_sem_queue_prepare(&tasks, q, -EIDRM);
		}
		list_for_each_entry_safe(q, tq, &sem->pending_alter, list) {
			unlink_queue(sma, q);
			wake_up_sem_queue_prepare(&tasks, q, -EIDRM);
		}
	}


	sem_rmid(ns, sma);
	sem_unlock(sma, -1);
	rcu_read_unlock();

	wake_up_sem_queue_do(&tasks);
	ns->used_sems -= sma->sem_nsems;
	ipc_rcu_putref(sma, sem_rcu_free);
}
