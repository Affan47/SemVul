mem_cgroup_id_put_many(struct mem_cgroup *memcg, unsigned int n)
{
	if (atomic_sub_and_test(n, &memcg->id.ref)) {
		idr_remove(&mem_cgroup_idr, memcg->id.id);
		memcg->id.id = 0;


		css_put(&memcg->css);
	}
}
