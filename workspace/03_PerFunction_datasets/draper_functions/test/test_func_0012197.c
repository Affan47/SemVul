free_arg_dim(void *data)
{
    int ** arg_dim_list = (int **)data;
    int i;

    for (i = 0; ; i++) {
	if (arg_dim_list[i] != NULL) {
	    if (arg_dim_list[i][-2] == -1)
		break;
	    free(&arg_dim_list[i][-3]);
	    arg_dim_list[i] = NULL;
	}
    }
    free(&arg_dim_list[i][-3]);
    arg_dim_list[i] = NULL;
    free(arg_dim_list);
}
