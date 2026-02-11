command_get_context_cache_client(void * x) {
    GetContextArgs * args = (GetContextArgs *)x;
    Channel * c  = cache_channel();
    Context * ctx = NULL;
    int frame = STACK_NO_FRAME;
    RegisterDefinition * reg_def = NULL;
    Trap trap;

    if (set_trap(&trap)) {
        if (id2register(args->id, &ctx, &frame, &reg_def) < 0) exception(errno);
        clear_trap(&trap);
    }

    cache_exit();

    write_stringz(&c->out, "R");
    write_stringz(&c->out, args->token);
    write_errno(&c->out, trap.error);
    if (reg_def != NULL) {
        write_context(&c->out, args->id, ctx, frame, reg_def);
    }
    else {
        write_stringz(&c->out, "null");
    }
    write_stream(&c->out, MARKER_EOM);
}
