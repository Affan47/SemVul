load_modules()
{
    dico_iterator_t itr = xdico_list_iterator(modinst_list);
    dicod_module_instance_t *inst;

    for (inst = dico_iterator_first(itr); inst;
	 inst = dico_iterator_next(itr)) {
	if (dicod_load_module(inst)) {
	    database_remove_dependent(inst);
	    dico_iterator_remove_current(itr, NULL);
	}
    }
    dico_iterator_destroy(&itr);
}
