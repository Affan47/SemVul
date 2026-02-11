modbus_reply_exception(modbus_t *ctx, const uint8_t *req,
                           unsigned int exception_code)
{
    int offset = ctx->backend->header_length;
    int slave = req[offset - 1];
    int function = req[offset];
    uint8_t rsp[MAX_MESSAGE_LENGTH];
    int rsp_length;
    int dummy_length = 99;
    sft_t sft;

    if (ctx == NULL) {
        errno = EINVAL;
        return -1;
    }

    sft.slave = slave;
    sft.function = function + 0x80;;
    sft.t_id = ctx->backend->prepare_response_tid(req, &dummy_length);
    rsp_length = ctx->backend->build_response_basis(&sft, rsp);


    if (exception_code < MODBUS_EXCEPTION_MAX) {
        rsp[rsp_length++] = exception_code;
        return send_msg(ctx, rsp, rsp_length);
    } else {
        errno = EINVAL;
        return -1;
    }
}
