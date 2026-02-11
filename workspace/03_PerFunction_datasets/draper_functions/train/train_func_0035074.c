getglyph(font_t *f, glui32 cid, int *adv, bitmap_t **glyphs)
{
    if (cid < 256)
    {
        if ((f->lowloaded[cid/8] & (1 << (cid%8))) == 0)
            loadglyph(f, cid);
        *adv = f->lowadvs[cid];
        *glyphs = f->lowglyphs[cid];
    }
    else
    {
        int idx = findhighglyph(cid, f->highentries, f->num_highentries);
        if (idx < 0)
        {
            loadglyph(f, cid);
            idx = ~idx;
        }
        *adv = f->highentries[idx].adv;
        *glyphs = f->highentries[idx].glyph;
    }
}
