hmdf_get_mtg_table(const Block *block_head)
{
    Mtg_table *mtg_ptr;
    Boolean found = FALSE;
    int _mtg_id;
    const Block *bptr;

    if (!block_head) {
	return NULL;
    }
    else if (!block_head->outer && block_head->hmdf) {
	bptr = block_head;
    }
    else {
	for (bptr = block_head->outer; bptr && !bptr->hmdf;
	     bptr = bptr->outer);
    }

    _mtg_id = bptr->hmdf->mtg_id;

    for (mtg_ptr = mtg_head; mtg_ptr && !found; mtg_ptr = mtg_ptr->next) {
	if (mtg_ptr->mtg_id == _mtg_id) {
	    found = TRUE;
	}
    }

    return mtg_ptr;
}
