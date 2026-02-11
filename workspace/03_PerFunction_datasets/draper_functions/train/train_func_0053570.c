command_set(char * token, Channel * c) {
    MemoryCommandArgs * args = read_command_args(token, c, CMD_SET);
    if (args != NULL) post_safe_event(args->ctx->mem, safe_memory_set, args);
}
