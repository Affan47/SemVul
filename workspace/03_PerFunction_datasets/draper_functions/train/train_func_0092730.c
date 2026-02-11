append_fragment_nonoptimizing(char alang, size_t asize, Append_fragment_info* info) {
	const String::Language lang=(String::Language)(unsigned char)alang;

	info->dest_languages->append(info->dest_body_plan_length,
		lang==String::L_TAINTED?
			info->lang
			:lang,
		asize);
	info->dest_body_plan_length+=asize;

	return 0;
}
