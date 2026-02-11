tomoyo_delete_domain(char *domainname)
{
	struct tomoyo_domain_info *domain;
	struct tomoyo_path_info name;

	name.name = domainname;
	tomoyo_fill_path_info(&name);
	if (mutex_lock_interruptible(&tomoyo_policy_lock))
		return -EINTR;

	list_for_each_entry_rcu(domain, &tomoyo_domain_list, list) {

		if (domain == &tomoyo_kernel_domain)
			continue;
		if (domain->is_deleted ||
		    tomoyo_pathcmp(domain->domainname, &name))
			continue;
		domain->is_deleted = true;
		break;
	}
	mutex_unlock(&tomoyo_policy_lock);
	return 0;
}
