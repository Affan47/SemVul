policy_view_capable(struct aa_ns *ns)
{
	struct user_namespace *user_ns = current_user_ns();
	struct aa_ns *view_ns = aa_get_current_ns();
	bool root_in_user_ns = uid_eq(current_euid(), make_kuid(user_ns, 0)) ||
			       in_egroup_p(make_kgid(user_ns, 0));
	bool response = false;
	if (!ns)
		ns = view_ns;

	if (root_in_user_ns && aa_ns_visible(view_ns, ns, true) &&
	    (user_ns == &init_user_ns ||
	     (unprivileged_userns_apparmor_policy != 0 &&
	      user_ns->level == view_ns->level)))
		response = true;
	aa_put_ns(view_ns);

	return response;
}
