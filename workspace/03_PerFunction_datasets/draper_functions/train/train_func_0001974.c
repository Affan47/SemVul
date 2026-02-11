px_put_data_length(stream * s, uint num_bytes)
{
    if (num_bytes > 255) {
        spputc(s, pxt_dataLength);
        px_put_l(s, (ulong) num_bytes);
    } else {
        spputc(s, pxt_dataLengthByte);
        spputc(s, (byte) num_bytes);
    }
}
