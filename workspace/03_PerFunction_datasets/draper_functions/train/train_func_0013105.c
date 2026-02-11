memcg_has_children(struct mem_cgroup *memcg)
{
	bool ret;


	lockdep_assert_held(&memcg_create_mutex);

	rcu_read_lock();
	ret = css_next_child(NULL, &memcg->css);
	rcu_read_unlock();
	return ret;
}
