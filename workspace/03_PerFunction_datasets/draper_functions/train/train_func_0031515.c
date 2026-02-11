alloc_array(VMG_ unsigned long ele_count)
{
    unsigned long ele_rem;
    size_t slot_cnt;
    size_t alloc_size;
    size_t i;


    slot_cnt = (ele_count == 0 ? 0 : ((size_t)((ele_count - 1) >> 28) + 1));


    alloc_size = 4 + slot_cnt*sizeof(char **);
    ext_ = (char *)G_mem->get_var_heap()->alloc_mem(alloc_size, this);


    set_element_count(ele_count);


    for (ele_rem = ele_count, i = 0 ; i < slot_cnt ; ++i)
    {
        unsigned char **pgtab;
        unsigned long pgcnt;
        size_t pg;


        pgcnt = ((ele_rem - 1) >> 15) + 1;
        if (pgcnt > 8*1024)
            pgcnt = 8*1024;


        pgtab = (unsigned char **)t3malloc(
            (size_t)(pgcnt * sizeof(unsigned char *)));


        get_page_table_array()[i] = pgtab;


        for (pg = 0 ; pg < pgcnt ; ++pg)
        {
            size_t pgsiz;


            pgsiz = 32*1024;
            if (pgsiz > ele_rem)
                pgsiz = (size_t)ele_rem;


            ele_rem -= pgsiz;


            pgtab[pg] = (unsigned char *)t3malloc(pgsiz);
        }
    }
}
