AssignModeID (int w, int h, int *unkcnt)
{
    int i;

#ifdef NEWMODES2
    return 0x40000000 | (w << 14) | h;
#endif
    for (i = 0; mi[i].width > 0; i++) {
        if (w == mi[i].width && h == mi[i].height)
            return 0x50001000 | (mi[i].id * 0x10000);
    }
    (*unkcnt)++;
    write_log (_T("P96: Non-unique mode %dx%d\n"), w, h);
    return 0x51001000 - (*unkcnt) * 0x10000;
}
