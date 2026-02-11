mar_flush (PJDEC_INST g, UINT marker)
{
    if (marker==MARKER_SOI || marker==MARKER_EOI ||
        (marker>=MARKER_RST0 && marker<=MARKER_RST7))
        return;

    read_skip_forward (g, read_uint(g) - 2);
}
