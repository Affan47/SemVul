make_convert_sb_mt_output_debug_info(Convert_sb_mt *cvsm_head, table_type type)
{
    Convert_sb_mt *cvsm = NULL;
    Block *bpt = NULL;

    if (cvsm_head == NULL)
        return;

    switch (type) {
    case DLG_TABLE:
        mfprintf(stdout, "<<-- to_sb_target(dlg) -->>\n");
        break;
    case CAR_TABLE:
        mfprintf(stdout, "<<-- to_sb_target(car) -->>\n");
        break;
    case DLG_CAR_TABLE:
        mfprintf(stdout, "<<-- to_sb_target(dlg & car) -->>\n");
        break;
    default:
        break;
    }

    for (cvsm = cvsm_head; cvsm != NULL; cvsm = cvsm->next) {
        bpt = cvsm->to_sb_block;

        if (bpt->dlg_tag > 0) {
            mfprintf(stdout, "%B: tlg%d.dlg%d\n",
                     bpt, bpt->tlg_tag, bpt->dlg_tag);
        }
        else if (bpt->car_tag > 0) {
            mfprintf(stdout, "%B: tlg%d.car%d\n",
                     bpt, bpt->tlg_tag, bpt->car_tag);
        }
    }

    switch (type) {
    case DLG_TABLE:
        mfprintf(stdout, "<<-- has dlg_tag block(example one dlg) -->>\n");
        print_dlg_inner_structure(cvsm_head->to_sb_block->inner);
        break;
    case CAR_TABLE:
        mfprintf(stdout, "<<-- has dlg_tag block(example one car) -->>\n");
        print_dlg_inner_structure(cvsm_head->to_sb_block->inner);
        break;
    case DLG_CAR_TABLE:
        mfprintf(stdout, "<<-- has dlg_tag block(example one dlg) -->>\n");
        print_dlg_inner_structure(cvsm_head->to_sb_block->inner);
        mfprintf(stdout, "<<-- has dlg_tag block(example one car) -->>\n");
        print_dlg_inner_structure(cvsm_head->next->to_sb_block->inner);
        break;
    default:
        break;
    }
}
