cmd_write_page_rect_cmd(gx_device_clist_writer * cldev, int op)
{


    int rcsize = 1 + 4 * cmd_sizew(0);
    byte *dp;
    int x = 0, y = 0, width = 0, height = 0;
    gx_clist_state *pcls1;
    int code;

    if_debug0m('L', cldev->memory, "[L]fillpage beg\n");
    code = set_cmd_put_all_op(dp, cldev, op, rcsize);
    if (code < 0)
        return code;
    for (pcls1 = cldev->states; pcls1 < cldev->states + cldev->nbands; pcls1++)
        cmd_set_rect(pcls1->rect);
    ++dp;
    cmd_putw(0, dp);
    cmd_putw(0, dp);
    cmd_putw(0, dp);
    cmd_putw(0, dp);
    if_debug0m('L', cldev->memory, "[L]fillpage end\n");
    return 0;
}
