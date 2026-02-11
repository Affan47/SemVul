read_put_params(command_buf_t *pcb, gs_imager_state *pis,
                gx_device_clist_reader *cdev, gs_memory_t *mem)
{
    const byte *cbp = pcb->ptr;
    gs_c_param_list param_list;
    uint cleft;
    uint rleft;
    bool alloc_data_on_heap = false;
    byte *param_buf;
    uint param_length;
    int code;

    cmd_get_value(param_length, cbp);
    if_debug1m('L', mem, " length=%d\n", param_length);
    if (param_length == 0) {
        code = 1;
        goto out;
    }


    code = top_up_cbuf(pcb, &cbp);
    if (code < 0)
        return code;
    if (pcb->end - cbp >= param_length) {
        param_buf = (byte *)cbp;
        cbp += param_length;
    } else {

        param_buf = gs_alloc_bytes(mem, param_length,
                                   "clist put_params");
        if (param_buf == 0) {
            code = gs_note_error(gs_error_VMerror);
            goto out;
        }
        alloc_data_on_heap = true;
        cleft = pcb->end - cbp;
        rleft = param_length - cleft;
        memmove(param_buf, cbp, cleft);
        pcb->end_status = sgets(pcb->s, param_buf + cleft, rleft, &rleft);
        cbp = pcb->end;
    }


    gs_c_param_list_write(&param_list, mem);
    code = gs_param_list_unserialize
        ( (gs_param_list *)&param_list, param_buf );
    if (code >= 0 && code != param_length)
        code = gs_error_unknownerror;
    if (code >= 0) {
        gs_c_param_list_read(&param_list);
        code = gs_imager_putdeviceparams(pis, (gx_device *)cdev,
                                         (gs_param_list *)&param_list);
    }
    gs_c_param_list_release(&param_list);
    if (alloc_data_on_heap)
        gs_free_object(mem, param_buf, "clist put_params");

out:
    pcb->ptr = cbp;
    return code;
}
