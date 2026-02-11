toDecoBuffer(OutBuffer *buf, int flag)
{
    if (flag != mod && flag != 0x100)
    {
        MODtoDecoBuffer(buf, mod);
    }
    buf->writestring("Nh");
    basetype->toDecoBuffer(buf, (flag & 0x100) ? 0 : mod);
}
