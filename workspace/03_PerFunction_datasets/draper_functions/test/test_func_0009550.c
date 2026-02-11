gfarm_id_adjust_next(struct gfarm_id_table *idtab)
{
	gfarm_int32_t id = idtab->id_next;
	int i;

	if (id >= idtab->id_limit) {
		gfarm_id_rewind(idtab);
		return;
	}

	if (idtab->hole_end >= idtab->idxsize ||
	    id < idtab->index[idtab->hole_end].id)
		return;

	i = idtab->hole_end;
#if 0
	assert(idtab->index[i].id == id &&
	    idtab->index[i].data != NULL);
#endif
	++id;
	++i;
	while (i < idtab->idxsize) {
		if (idtab->index[i].id > id ||
		    idtab->index[i].data == NULL)
			break;
		++id;
		++i;
	}
	if (id >= idtab->id_limit) {
		gfarm_id_rewind(idtab);
		return;
	}
	idtab->id_next = id;
	i -= idtab->hole_end;
	memmove(&idtab->index[idtab->hole_start],
	    &idtab->index[idtab->hole_end],
	    i * sizeof(struct gfarm_id_index));
	idtab->hole_start += i;
	idtab->hole_end += i;
	gfarm_id_shrink_head(idtab);
	gfarm_id_shrink_tail(idtab);
}
