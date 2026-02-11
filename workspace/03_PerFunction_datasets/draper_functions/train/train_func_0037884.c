default_image_path(void)
{
	const char *path = vm_executable_path();

	if(!path)
		return "factor.image";


	int len = 0;
	const char *iter = path;
	while(*iter) { len++; iter++; }

	char *new_path = safe_malloc(PATH_MAX + SUFFIX_LEN + 1);
	memcpy(new_path,path,len + 1);
	memcpy(new_path + len,SUFFIX,SUFFIX_LEN + 1);
	return new_path;
}
