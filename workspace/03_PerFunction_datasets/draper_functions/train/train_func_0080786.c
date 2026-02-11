umh_complete(struct subprocess_info *sub_info)
{
	struct completion *comp = xchg(&sub_info->complete, NULL);


	if (comp)
		complete(comp);
	else
		call_usermodehelper_freeinfo(sub_info);
}
