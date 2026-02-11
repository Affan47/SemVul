obj_is_rsakey(TSS_HOBJECT hObject)
{
	TSS_BOOL answer = FALSE;

	if ((obj_list_get_obj(&rsakey_list, hObject))) {
		answer = TRUE;
		obj_list_put(&rsakey_list);
	}

	return answer;
}
