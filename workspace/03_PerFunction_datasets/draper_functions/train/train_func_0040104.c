isns_dd_release(isns_dd_t *dd)
{
	isns_dd_member_t *member;

	if (dd == NULL || dd->dd_inserted)
		return;

	while ((member = dd->dd_members) != NULL) {
		dd->dd_members = member->ddm_next;
		isns_dd_member_free(member);
	}

	if (dd->dd_object)
		isns_object_release(dd->dd_object);

	isns_free(dd->dd_name);
	isns_free(dd);
}
