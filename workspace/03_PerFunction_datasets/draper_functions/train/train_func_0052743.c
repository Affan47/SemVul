_factory_free(void *dat, void *context)
{
    container_type *data = (container_type *)dat;
    if (data == NULL)
	return;

    if (data->name != NULL) {
        DEBUGMSGTL(("container", "  _factory_free_list() called for %s\n",
                    data->name));
	free(NETSNMP_REMOVE_CONST(void *, data->name));
    }
    free(data);
}
