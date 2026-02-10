process_loop(Node node, RfmBlock block)
{
    Rfm_loop_info_table loop_info_t;
    RfmLoopInfo         loop_info;

    loop_info = (RfmLoopInfo)memset(&loop_info_t, 0x00,
                                    sizeof(Rfm_loop_info_table));
    if (has_control_variable_loop(node, loop_info)) {
        block = process_do_loop(node, block, loop_info);
    } else if (node->THIRD_CHILD->SECOND_CHILD->SUB_CODE == 0x00) {
        block = process_bct_loop(node, block);
    } else {
        block = process_rb_loop(node, block);
    }
    return(block);
}
