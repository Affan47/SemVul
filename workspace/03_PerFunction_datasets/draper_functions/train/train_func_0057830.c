mca_rcache_vma_compare_regs(
        mca_mpool_base_registration_t *reg1,
        mca_mpool_base_registration_t *reg2)
{

    if((reg1->flags & MCA_MPOOL_FLAGS_PERSIST) &&
            !(reg2->flags & MCA_MPOOL_FLAGS_PERSIST))
        return 1;

    if(!(reg1->flags & MCA_MPOOL_FLAGS_PERSIST) &&
            (reg2->flags & MCA_MPOOL_FLAGS_PERSIST))
        return -1;

    if (reg1->bound != reg2->bound)
        return (int)(reg1->bound - reg2->bound);


    return (int)((uintptr_t)reg1 - (uintptr_t)reg2);
}
