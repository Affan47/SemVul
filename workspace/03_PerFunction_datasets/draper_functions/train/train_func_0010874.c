xylist_close(xylist_t* ls) {
    int rtn = 0;
    if (ls->table) {
        if (fitstable_close(ls->table)) {
			ERROR("Failed to close xylist table");
            rtn = -1;
        }
    }
    free(ls->antype);
	free(ls);
	return rtn;
}
