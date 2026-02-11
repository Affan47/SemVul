idtable_free_id(idtable_t *tbl, uint32 id)
{
	g_assert(idtable_is_id_used(tbl, id));

	htable_remove(tbl->ht, uint_to_pointer(id));
}
