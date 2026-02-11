utsns_install(struct nsproxy *nsproxy, struct ns_common *new)
{
	struct uts_namespace *ns = to_uts_ns(new);

	if (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(current_user_ns(), CAP_SYS_ADMIN))
		return -EPERM;

	get_uts_ns(ns);
	put_uts_ns(nsproxy->uts_ns);
	nsproxy->uts_ns = ns;
	return 0;
}
