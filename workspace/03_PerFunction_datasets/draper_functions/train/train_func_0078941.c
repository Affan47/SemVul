bcf_unpack_info_core1(uint8_t *ptr, bcf_info_t *info)
{
    uint8_t *ptr_start = ptr;
    info->key = bcf_dec_typed_int1(ptr, &ptr);
    info->len = bcf_dec_size(ptr, &ptr, &info->type);
    info->vptr = ptr;
    info->vptr_off  = ptr - ptr_start;
    info->vptr_free = 0;
    info->v1.i = 0;
    if (info->len == 1) {
        if (info->type == BCF_BT_INT8 || info->type == BCF_BT_CHAR) info->v1.i = *(int8_t*)ptr;
        else if (info->type == BCF_BT_INT32) info->v1.i = *(int32_t*)ptr;
        else if (info->type == BCF_BT_FLOAT) info->v1.f = *(float*)ptr;
        else if (info->type == BCF_BT_INT16) info->v1.i = *(int16_t*)ptr;
    }
    ptr += info->len << bcf_type_shift[info->type];
    info->vptr_len = ptr - info->vptr;
    return ptr;
}
