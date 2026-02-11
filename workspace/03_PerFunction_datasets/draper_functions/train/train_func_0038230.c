libbdplus_mmap(BD_BDPLUS *p, uint32_t region_id, void *mem)
{
    if (p && p->bdplus) {
        DL_CALL(p->h_libbdplus, bdplus_mmap, p->bdplus, region_id, mem);
    }
}
