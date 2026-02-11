writeUTF16(unsigned w)
{
    reserve(4);
    if (w <= 0xFFFF)
    {
        *(unsigned short *)(this->data + offset) = (unsigned short)w;
        offset += 2;
    }
    else if (w <= 0x10FFFF)
    {
        *(unsigned short *)(this->data + offset) = (unsigned short)((w >> 10) + 0xD7C0);
        *(unsigned short *)(this->data + offset + 2) = (unsigned short)((w & 0x3FF) | 0xDC00);
        offset += 4;
    }
    else
        assert(0);
}
