save_p96 (int *len, uae_u8 *dstptr)
{
    uae_u8 *dstbak, *dst;
    int i;

    if (currprefs.rtgmem_size == 0)
        return NULL;
    if (dstptr)
        dstbak = dst = dstptr;
    else
        dstbak = dst = xmalloc (uae_u8, 1000);
    save_u32 (2);
    save_u32 ((picasso_on ? 1 : 0) | (set_gc_called ? 2 : 0) | (set_panning_called ? 4 : 0) |
        (hwsprite ? 8 : 0) | (cursorvisible ? 16 : 0) | (interrupt_enabled ? 32 : 0) | 64);
    save_u32 (currprefs.rtgmem_size);
    save_u32 (picasso96_state.Address);
    save_u32 (picasso96_state.RGBFormat);
    save_u16 (picasso96_state.Width);
    save_u16 (picasso96_state.Height);
    save_u16 (picasso96_state.VirtualWidth);
    save_u16 (picasso96_state.VirtualHeight);
    save_u16 (picasso96_state.XOffset);
    save_u16 (picasso96_state.YOffset);
    save_u8 (picasso96_state.GC_Depth);
    save_u8 (picasso96_state.GC_Flags);
    save_u16 (picasso96_state.BytesPerRow);
    save_u8 (picasso96_state.BytesPerPixel);
    save_u32 (uaegfx_base);
    save_u32 (uaegfx_rom);
    save_u32 (boardinfo);
    for (i = 0; i < 4; i++)
        save_u32 (cursorrgb[i]);
    for (i = 0; i < 256; i++) {
        save_u8 (picasso96_state.CLUT[i].Red);
        save_u8 (picasso96_state.CLUT[i].Green);
        save_u8 (picasso96_state.CLUT[i].Blue);
    }
    *len = dst - dstbak;
    return dstbak;
}
