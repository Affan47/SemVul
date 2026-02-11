nv_split(char *buf, struct nv_pair *nv)
{

	char *ptr;

	nv->name = NULL;
	nv->value = NULL;
	nv->option = NULL;
	ptr = strtok(buf, " ");
	if (ptr == NULL)
		return 0;
	if (ptr[0] == '#')
		return 0;
	nv->name = ptr;


	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;
	if (strcmp(ptr, "=") != 0)
		return 2;


	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 1;
	nv->value = ptr;


	return 0;
}
