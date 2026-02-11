gcov_info_unlink(struct gcov_info *prev, struct gcov_info *info)
{
	if (prev)
		prev->next = info->next;
	else
		gcov_info_head = info->next;
}
