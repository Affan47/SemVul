gf_mem_set_acct_info (xlator_t *xl, char **alloc_ptr,
                      size_t size, uint32_t type)
{

        char    *ptr = NULL;

        if (!alloc_ptr)
                return;

        ptr = (char *) (*alloc_ptr);

        GF_ASSERT (xl != NULL);

        GF_ASSERT (xl->mem_acct.rec != NULL);

        GF_ASSERT (type <= xl->mem_acct.num_types);

        LOCK(&xl->mem_acct.rec[type].lock);
        {
                xl->mem_acct.rec[type].size += size;
                xl->mem_acct.rec[type].num_allocs++;
                xl->mem_acct.rec[type].total_allocs++;
                xl->mem_acct.rec[type].max_size =
                        max (xl->mem_acct.rec[type].max_size,
                             xl->mem_acct.rec[type].size);
                xl->mem_acct.rec[type].max_num_allocs =
                        max (xl->mem_acct.rec[type].max_num_allocs,
                             xl->mem_acct.rec[type].num_allocs);
        }
        UNLOCK(&xl->mem_acct.rec[type].lock);

        *(uint32_t *)(ptr) = type;
        ptr = ptr + 4;
        memcpy (ptr, &size, sizeof(size_t));
        ptr += sizeof (size_t);
        memcpy (ptr, &xl, sizeof(xlator_t *));
        ptr += sizeof (xlator_t *);
        *(uint32_t *)(ptr) = GF_MEM_HEADER_MAGIC;
        ptr = ptr + 4;
        ptr = ptr + 8;
        *(uint32_t *) (ptr + size) = GF_MEM_TRAILER_MAGIC;

        *alloc_ptr = (void *)ptr;
        return;
}
