find_closest_existing_cb_scan_up( off64_t bnum, cbindex_t *start)
{
    cbindex_t *found;

    for( found = start; found->prev; found = found->prev) {
	if( found->bnum <= bnum)
	    break;
    }

    return found;
}
