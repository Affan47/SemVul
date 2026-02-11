find_acl_by_name(const char *name, struct list *head)
{
	struct acl *acl;
	list_for_each_entry(acl, head, list) {
		if (strcmp(acl->name, name) == 0)
			return acl;
	}
	return NULL;
}
