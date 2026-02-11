flip4x4(byte * buffer, const byte ** planes, int offset, int nbytes)
{
    byte *out = buffer;
    const byte *in1 = planes[0] + offset;
    const byte *in2 = planes[1] + offset;
    const byte *in3 = planes[2] + offset;
    const byte *in4 = planes[3] + offset;
    int n = nbytes;

    for (; n > 0; out += 4, ++in1, ++in2, ++in3, ++in4, --n) {
        byte_var b1 = *in1, b2 = *in2, b3 = *in3, b4 = *in4;

        out[0] = (b1 & 0xf0) | (b2 >> 4);
        out[1] = (b3 & 0xf0) | (b4 >> 4);
        out[2] = (byte) ((b1 << 4) | (b2 & 0xf));
        out[3] = (byte) ((b3 << 4) | (b4 & 0xf));
    }
    return 0;
}
