cx_fabric_get_param(cx_fabric_arg_t * arg_type_list,
				       char *arg)
{
	int i;

	errno = 0;

	i = 0;
	while (arg_type_list[i].keyword != NULL) {
		if (!strncasecmp(arg, arg_type_list[i].keyword,
				 strlen(arg_type_list[i].keyword))) {
			return ((cx_fabric_param_t *) arg_type_list[i].data);
		}
		i++;
	}
	return NULL;
}
