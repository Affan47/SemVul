free_reach_def_list(List *rd_head)
{
    List *rd_list;
    Reach_def *rd;

    for (rd_list = rd_head; rd_list != NULL; rd_list = rd_list->next) {
	rd = rd_list->data;
	list_free(rd->def_stm);
	free(rd);
	rd = NULL;
    }
    list_free(rd_head);
}
