is_main_block_head(Ctrl_task *c, proc_kind proc)
{
    Block_info *b_info = ctrl_task_get_b_info(c);
    Block *block = block_info_get_block(b_info);

    return (proc == PROC_CPU
            && block->outer == NULL
            && block->module->kind == MODULE_MAIN);
}
