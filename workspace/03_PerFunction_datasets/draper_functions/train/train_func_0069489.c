midi_cont(boolean onflag)
{
    if (!initialized) fixup();
    if (onflag) {
#ifdef AMIGA
    SetMidiFilters(cmt_mi, cmt_mi->PortFilter,
        cmt_mi->TypeFilter | CONTCONT, cmt_mi->ChanFilter);
#endif
#ifdef  DOS
#ifndef WINDOWS
    mPutCmd(BENDERON);
#endif
#endif
    } else {
#ifdef AMIGA
    SetMidiFilters(cmt_mi, cmt_mi->PortFilter,
        cmt_mi->TypeFilter & ~CONTCONT, cmt_mi->ChanFilter);
#endif
    }
#ifdef MACINTOSH_OR_DOS
    ctrlFilter = !onflag;
#endif
    if (musictrace) gprintf(TRANS,"midi_cont: %d\n", onflag);
}
