H5D_chunk_cache_evict(const H5D_t *dset, hid_t dxpl_id, const H5D_dxpl_cache_t *dxpl_cache,
    H5D_rdcc_ent_t *ent, hbool_t flush)
{
    H5D_rdcc_t *rdcc = &(dset->shared->cache.chunk);
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5D_chunk_cache_evict)

    HDassert(dset);
    HDassert(dxpl_cache);
    HDassert(ent);
    HDassert(!ent->locked);
    HDassert(ent->idx < rdcc->nslots);

    if(flush) {

	if(H5D_chunk_flush_entry(dset, dxpl_id, dxpl_cache, ent, TRUE) < 0)
	    HGOTO_ERROR(H5E_IO, H5E_WRITEERROR, FAIL, "cannot flush indexed storage buffer")
    }
    else {

	if(ent->chunk != NULL)
	    ent->chunk = (uint8_t *)H5D_chunk_xfree(ent->chunk, &(dset->shared->dcpl_cache.pline));
    }


    if(ent->prev)
	ent->prev->next = ent->next;
    else
	rdcc->head = ent->next;
    if(ent->next)
	ent->next->prev = ent->prev;
    else
	rdcc->tail = ent->prev;
    ent->prev = ent->next = NULL;


    rdcc->slot[ent->idx] = NULL;
    ent->idx = UINT_MAX;
    rdcc->nbytes_used -= dset->shared->layout.u.chunk.size;
    --rdcc->nused;


    ent = H5FL_FREE(H5D_rdcc_ent_t, ent);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
