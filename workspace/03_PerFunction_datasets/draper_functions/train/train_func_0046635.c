clamp_align(unsigned int align)
{
    unsigned int packing = (pointer_size == 4) ? win32_packing : win64_packing;
    if(align > packing) align = packing;
    return align;
}
