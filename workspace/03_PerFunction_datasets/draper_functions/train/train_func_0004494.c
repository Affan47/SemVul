write_context(OutputStream * out, char * id, Context * ctx, int level, StackFrame * frame, StackFrame * down) {
    uint64_t v;
    RegisterDefinition * reg_def = get_PC_definition(ctx);

    write_stream(out, '{');

    json_write_string(out, "ID");
    write_stream(out, ':');
    json_write_string(out, id);

    write_stream(out, ',');
    json_write_string(out, "ParentID");
    write_stream(out, ':');
    json_write_string(out, ctx->id);

    write_stream(out, ',');
    json_write_string(out, "Level");
    write_stream(out, ':');
    json_write_long(out, level);

    write_stream(out, ',');
    json_write_string(out, "ProcessID");
    write_stream(out, ':');
    json_write_string(out, ctx->mem->id);

    if (frame->is_top_frame) {
        write_stream(out, ',');
        json_write_string(out, "TopFrame");
        write_stream(out, ':');
        json_write_boolean(out, 1);
    }

    if (frame->fp) {
        write_stream(out, ',');
        json_write_string(out, "FP");
        write_stream(out, ':');
        json_write_uint64(out, frame->fp);
    }

    if (read_reg_value(frame, reg_def, &v) == 0) {
        write_stream(out, ',');
        json_write_string(out, "IP");
        write_stream(out, ':');
        json_write_uint64(out, v);
    }

    if (down != NULL && read_reg_value(down, reg_def, &v) == 0) {
        write_stream(out, ',');
        json_write_string(out, "RP");
        write_stream(out, ':');
        json_write_uint64(out, v);
    }

    write_stream(out, '}');
}
