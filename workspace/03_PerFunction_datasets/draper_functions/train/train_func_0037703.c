add_mode (struct MultiDisplay *md, int w, int h, int d, int freq,
        int lace) {
    int ct;
    int i, j;


    int rawmode = 0;

    ct = 0;
    if (d == 8)
        ct = RGBMASK_8BIT;
    if (d == 15)
        ct = RGBMASK_15BIT;
    if (d == 16)
        ct = RGBMASK_16BIT;
    if (d == 24)
        ct = RGBMASK_24BIT;
    if (d == 32)
        ct = RGBMASK_32BIT;
    if (ct == 0)
        return;
    d /= 8;
    i = 0;
    while (md->DisplayModes[i].depth >= 0) {
        if (md->DisplayModes[i].depth == d && md->DisplayModes[i].res.width == w && md->DisplayModes[i].res.height == h) {
            for (j = 0; j < MAX_REFRESH_RATES; j++) {
                if (md->DisplayModes[i].refresh[j] == 0 || md->DisplayModes[i].refresh[j] == freq)
                    break;
            }
            if (j < MAX_REFRESH_RATES) {
                md->DisplayModes[i].refresh[j] = freq;
                md->DisplayModes[i].refreshtype[j] = rawmode;
                md->DisplayModes[i].refresh[j + 1] = 0;
                return;
            }
        }
        i++;
    }
    i = 0;
    while (md->DisplayModes[i].depth >= 0)
        i++;
    if (i >= MAX_PICASSO_MODES - 1)
        return;
    md->DisplayModes[i].rawmode = rawmode;
    md->DisplayModes[i].lace = lace;
    md->DisplayModes[i].res.width = w;
    md->DisplayModes[i].res.height = h;
    md->DisplayModes[i].depth = d;
    md->DisplayModes[i].refresh[0] = freq;
    md->DisplayModes[i].refreshtype[0] = rawmode;
    md->DisplayModes[i].refresh[1] = 0;
    md->DisplayModes[i].colormodes = ct;
    md->DisplayModes[i + 1].depth = -1;
    _stprintf (md->DisplayModes[i].name, _T("%dx%d%s, %d-bit"),
        md->DisplayModes[i].res.width, md->DisplayModes[i].res.height,
        lace ? _T("i") : _T(""),
        md->DisplayModes[i].depth * 8);
}
