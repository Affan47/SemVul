__alloc_cpin(int32 has_name)
{
 struct cell_pin_t *cpp;

 cpp = alloc_memcpins();
 if (has_name) cpp->pnam = alloc_cpnam(__portnam);
 else cpp->pnam = NULL;
 cpp->cplin_cnt = __lin_cnt;
 cpp->cpfnam_ind = __cur_fnam_ind;
 cpp->cpxnd = NULL;
 cpp->cpnxt = NULL;

 return(cpp);
}
