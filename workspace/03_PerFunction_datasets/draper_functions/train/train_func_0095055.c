read_abbrev_value(struct bc_read_stream *stream, struct abbrev_operand *op)
{
    if(op->type == Literal)
        return op->o.literal_value;
    else
    {
        switch(op->o.encoding_info.encoding) {
            case OP_ENCODING_FIXED:
                return read_fixed_64(stream, op->o.encoding_info.value);
            case OP_ENCODING_VBR:
                return read_vbr_64(stream, op->o.encoding_info.value);
            case OP_ENCODING_CHAR6:
                return decode_char6(read_fixed(stream, 6));
            default:
                stream->stream_err |= BITCODE_ERR_INTERNAL;
                return 0;
        }
    }
}
