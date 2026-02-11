make_new_hmdf_block(Block *bpt, Hmdf_table *parent)
{
    Module_table *module;

    switch (bpt->kind) {

    case LOOP:
    case RB:
    case BLOCK:
        make_new_hmdf_info(bpt, parent);
        break;

    case DOALL:
    case DOSUM:
    case DOACR:
        make_new_hmdf_info(bpt, parent);
        bpt->kind = LOOP;
        break;

    case SB:
        module = bpt->sb_head->module;
        if (module->block_head->hmdf == NULL)
            make_new_hmdf_info(module->block_head, parent);
        break;

    default:
        fatal("dame kind\n");
    }

#if 1
    mfprintf(stdout, "hmdf(inner)\n");
    mfprintf(stdout, "=== %B ===\n", bpt);
    mfprintf(stdout,
             "size = %d, pc = %d, pe = %d\n",
             bpt->total_array_size,
             bpt->hmdf->pc_num,
             bpt->hmdf->pe_num);
#endif

}
