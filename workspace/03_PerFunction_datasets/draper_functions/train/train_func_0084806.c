deinit_S(void)
{
#if ENABLE_FEATURE_EDITING_FANCY_PROMPT


	free((char*)cmdedit_prompt);
#endif
#if ENABLE_USERNAME_OR_HOMEDIR
	free(user_buf);
	if (home_pwd_buf != null_str)
		free(home_pwd_buf);
#endif
	free(lineedit_ptr_to_statics);
}
