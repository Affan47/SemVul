set_haschildren(char *name, int matchlen,
			   int maycreate __attribute__((unused)),
			   int *attributes)
{
    list_callback_calls++;
    if (name[matchlen]) {
	*attributes |= MBOX_ATTRIBUTE_HASCHILDREN;
	return CYRUSDB_DONE;
    }
    return 0;
}
