netsnmp_clear_callback_list(void)
{

    netsnmp_transport_list *list = trlist, *next = NULL;
    netsnmp_transport *tr = NULL;

    DEBUGMSGTL(("callback_clear", "called netsnmp_callback_clear_list()\n"));
    while (list != NULL) {
	next = list->next;
	tr = list->transport;

	if (tr != NULL) {
	    tr->f_close(tr);
  	    netsnmp_transport_remove_from_list(&trlist, tr);
	    netsnmp_transport_free(tr);
	}
	list = next;
    }
    trlist = NULL;

}
