PushGlobalBookmark() {
    EPoint P = CP;

    P.Row = VToR(P.Row);
    EMark *m = markIndex.pushMark(this, P);
    if (m)
         Msg(S_INFO, "Placed bookmark %s", m->GetName());
    return m ? 1 : 0;
}
