gfarm_id_shrink_tail(struct gfarm_id_table *idtab)
{
	while (idtab->hole_end < idtab->idxsize) {
		if (idtab->index[idtab->hole_end].data != NULL)
			break;
		++idtab->hole_end;
		--idtab->tail_free;
	}
}
