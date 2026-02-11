yama_ptracer_add(struct task_struct *tracer,
			    struct task_struct *tracee)
{
	struct ptrace_relation *relation, *added;

	added = kmalloc(sizeof(*added), GFP_KERNEL);
	if (!added)
		return -ENOMEM;

	added->tracee = tracee;
	added->tracer = tracer;
	added->invalid = false;

	spin_lock(&ptracer_relations_lock);
	rcu_read_lock();
	list_for_each_entry_rcu(relation, &ptracer_relations, node) {
		if (relation->invalid)
			continue;
		if (relation->tracee == tracee) {
			list_replace_rcu(&relation->node, &added->node);
			kfree_rcu(relation, rcu);
			goto out;
		}
	}

	list_add_rcu(&added->node, &ptracer_relations);

out:
	rcu_read_unlock();
	spin_unlock(&ptracer_relations_lock);
	return 0;
}
