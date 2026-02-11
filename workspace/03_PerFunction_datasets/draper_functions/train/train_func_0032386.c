PTD_put_short(FILE * out, ULONG i)
{
    arb_assert(i == (unsigned short) i);
    int io;
    static unsigned char buf[2];
    PT_WRITE_SHORT(buf,i);
    io = buf[0]; putc(io,out);
    io = buf[1]; putc(io,out);
}
