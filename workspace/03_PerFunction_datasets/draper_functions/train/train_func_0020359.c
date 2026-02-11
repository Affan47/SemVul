trim_obj(gs_ref_memory_t *mem, obj_header_t *obj, uint size, chunk_t *cp)


{
    uint rounded_size = obj_align_round(size);
    obj_header_t *pre_obj = obj - 1;
    obj_header_t *excess_pre = (obj_header_t*)((char*)obj + rounded_size);
    uint old_rounded_size = obj_align_round(pre_obj->o_size);
    uint excess_size = old_rounded_size - rounded_size - sizeof(obj_header_t);


    pre_obj->o_size = size;
    if (old_rounded_size == rounded_size)
        return;


    if (pre_obj->o_alone) {
        if (!cp) {
            mem->cfreed.memory = mem;
            if (chunk_locate(obj, &mem->cfreed)) {
                cp = mem->cfreed.cp;
            }
        }
        if (cp) {
#ifdef DEBUG
            if (cp->cbot != (byte *)obj + old_rounded_size) {
                lprintf3("resizing 0x%lx, old size %u, new size %u, cbot wrong!\n",
                         (ulong)obj, old_rounded_size, size);

            } else
#endif
                {
                    cp->cbot = (byte *)excess_pre;
                    return;
                }
        }


        pre_obj->o_pad = 0;
        pre_obj->o_alone = 0;
    }

    excess_pre->o_type = &st_free;
    excess_pre->o_size = excess_size;
    excess_pre->o_pad = 0;
    excess_pre->o_alone = 0;
    if (excess_size >= obj_align_mod) {

        obj_header_t **pfl;

        if ((byte *)excess_pre >= mem->cc.int_freed_top)
            mem->cc.int_freed_top = (byte *)excess_pre + excess_size;
        if (excess_size <= max_freelist_size)
            pfl = &mem->freelists[(excess_size + obj_align_mask) >>
                                 log2_obj_align_mod];
        else {
            uint rounded_size = obj_align_round(excess_size);

            pfl = &mem->freelists[LARGE_FREELIST_INDEX];
            if (rounded_size > mem->largest_free_size)
                mem->largest_free_size = rounded_size;
        }
        *(obj_header_t **) (excess_pre + 1) = *pfl;
        *pfl = excess_pre + 1;
        mem->cfreed.memory = mem;
    } else {

        mem->lost.objects += excess_size + sizeof(obj_header_t);
    }
}
