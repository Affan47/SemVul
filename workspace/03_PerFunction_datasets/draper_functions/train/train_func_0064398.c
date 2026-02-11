css_clear_dir(struct cgroup_subsys_state *css,
			  struct cgroup *cgrp_override)
{
	struct cgroup *cgrp = cgrp_override ?: css->cgroup;
	struct cftype *cfts;

	list_for_each_entry(cfts, &css->ss->cfts, node)
		cgroup_addrm_files(css, cgrp, cfts, false);
}
