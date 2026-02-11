div_loop_modules(Module_table *module_top, Lad_opt *lad_opt)
{
    Module_table *mpt;
    List *tlg_list = NULL;

    for(mpt = module_top; mpt != NULL; mpt = mpt->next){
        if(mpt->block_head != NULL ){
            List *l = div_loop_blocks(mpt->block_head, lad_opt);
            tlg_list = list_concat(tlg_list, l);
        }
    }

    return tlg_list;
}
