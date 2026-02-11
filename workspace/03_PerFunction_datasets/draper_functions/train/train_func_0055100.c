change_number(mtg_list_type *head)
{
    mtg_list_type *p;
    mtg_type *mtg;
    for (p = head; p != NULL; p = p->next) {
	mtg = (mtg_type *)(p->cnt);
	change_number_tlg_list(mtg->tlg_list);
    }
}
