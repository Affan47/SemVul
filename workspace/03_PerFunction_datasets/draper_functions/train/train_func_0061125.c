write_commands(OutputStream * out, Context * ctx, StackTracingCommandSequence * seq) {
    if (seq != NULL) {
        int i;
        write_stream(out, '[');
        for (i = 0; i < seq->cmds_cnt; i++) {
            StackTracingCommand * cmd = seq->cmds + i;
            if (i > 0) write_stream(out, ',');
            json_write_long(out, cmd->cmd);
            switch (cmd->cmd) {
            case SFT_CMD_NUMBER:
                write_stream(out, ',');
                json_write_int64(out, cmd->num);
                break;
            case SFT_CMD_REGISTER:
                write_stream(out, ',');
                json_write_string(out, register2id(ctx, STACK_NO_FRAME, cmd->reg));
                break;
            case SFT_CMD_DEREF:
                write_stream(out, ',');
                json_write_ulong(out, cmd->size);
                write_stream(out, ',');
                json_write_boolean(out, cmd->big_endian);
                break;
            }
        }
        write_stream(out, ']');
    }
    else {
        write_string(out, "null");
    }
}
