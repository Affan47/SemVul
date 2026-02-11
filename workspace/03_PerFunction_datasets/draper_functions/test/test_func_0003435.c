zotentry(struct hdr_line *l)
{
    register struct hdr_line *ld, *lf = l;

    while((ld = lf) != NULL){
	lf = ld->next;
	ld->next = ld->prev = NULL;
	free((char *) ld);
    }
}
