add_preprocessor_define(char *define)
{
	struct _defines *pd = defines;
	char	   *ptr,
			   *define_copy = mm_strdup(define);

	defines = mm_alloc(sizeof(struct _defines));


	ptr = strchr(define_copy, '=');
	if (ptr != NULL)
	{
		char	   *tmp;


		for (tmp = ptr - 1; *tmp == ' '; tmp--);
		tmp[1] = '\0';
		defines->old = define_copy;
		defines->new = ptr + 1;
	}
	else
	{
		defines->old = define_copy;
		defines->new = mm_strdup("1");
	}
	defines->pertinent = true;
	defines->used = NULL;
	defines->next = pd;
}
