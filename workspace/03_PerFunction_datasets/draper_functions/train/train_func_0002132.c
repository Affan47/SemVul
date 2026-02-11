print_mtg_id_for_layer_ctrl(Ctrl_task *c)
{
    Block_info *b_info = ctrl_task_get_b_info(c);
    Block *block = block_info_get_block(b_info);
    int mtg_id = -1;

    if (block->hmdf != NULL) mtg_id = block->hmdf->mtg_id;

    if (mtg_id != -1) fprintf(info_fp, "##### mtg_id : %d #####\n", mtg_id);

}
