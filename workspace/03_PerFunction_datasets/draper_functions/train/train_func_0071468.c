loop_restr_dist(Module_table *module_head,
                Boolean log_out_flag)
{
    Module_table *module;
    Boolean      dist_flag;

    log_out = log_out_flag;
    if (log_out) {
        mainlog("--- loop restr dist ---");
    }

    dist_flag = FALSE;

    module = module_head;
    while(module != NULL) {

#ifdef DEBUG
        if (log_out) {
            memset(buffer, '\0', 256);
            sprintf(buffer, "--- module No.%d ---",module->entry);
            mainlog(buffer);
        }
#endif

        if (module->kind != MODULE_BLOCKDATA) {
            if (seek_loop_restr_dist(module->block_head, 0)) {
                dist_flag = TRUE;
            }
        }

        module = module->next;
    }

    return dist_flag;
}
