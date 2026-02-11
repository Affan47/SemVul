_sasl_done_with_plugins(void)
{
#ifdef DO_DLOPEN
    lib_list_t *libptr, *libptr_next;

    for(libptr = lib_list_head; libptr; libptr = libptr_next) {
	libptr_next = libptr->next;
	if(libptr->library)
	    dlclose(libptr->library);
	sasl_FREE(libptr);
    }

    lib_list_head = NULL;
#endif
    return SASL_OK;
}
