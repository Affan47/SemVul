command_get_children_cache_client(void * x) {
    GetChildrenArgs * args = (GetChildrenArgs *)x;
    Channel * c  = cache_channel();
    Context * ctx = NULL;
    int frame = STACK_NO_FRAME;
    StackFrame * frame_info = NULL;
    RegisterDefinition * defs = NULL;
    Trap trap;

    if (set_trap(&trap)) {
        if (id2frame(args->id, &ctx, &frame) == 0) {
            if (get_frame_info(ctx, frame, &frame_info) < 0) exception(errno);
        }
        else {
            ctx = id2ctx(args->id);
            frame = STACK_TOP_FRAME;
        }
        if (ctx != NULL) defs = get_reg_definitions(ctx);
        clear_trap(&trap);
    }

    cache_exit();

    write_stringz(&c->out, "R");
    write_stringz(&c->out, args->token);

    write_errno(&c->out, trap.error);

    write_stream(&c->out, '[');
    if (defs != NULL) {
        int cnt = 0;
        RegisterDefinition * reg_def;
        for (reg_def = defs; reg_def->name != NULL; reg_def++) {
            if (frame == STACK_TOP_FRAME || read_reg_value(frame_info, reg_def, NULL) == 0) {
                if (cnt > 0) write_stream(&c->out, ',');
                json_write_string(&c->out, register2id(ctx, frame, reg_def));
                cnt++;
            }
        }
    }
    write_stream(&c->out, ']');
    write_stream(&c->out, 0);

    write_stream(&c->out, MARKER_EOM);
}
