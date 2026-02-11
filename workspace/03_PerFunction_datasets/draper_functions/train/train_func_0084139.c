start_done(int error, Context * ctx, void * arg) {
    AttachDoneArgs * data = (AttachDoneArgs *)arg;
    Channel * c = data->c;

    if (!is_channel_closed(c)) {
        write_stringz(&c->out, "R");
        write_stringz(&c->out, data->token);
        write_errno(&c->out, error);
        if (ctx == NULL) write_string(&c->out, "null");
        else write_context(&c->out, id2pid(ctx->id, NULL));
        write_stream(&c->out, 0);
        write_stream(&c->out, MARKER_EOM);
    }
    channel_unlock(c);
    loc_free(data);
}
