TagLoad(ExState &State) {
    char Tag[MAXPATH];
    char FullTag[MAXPATH];

    const char* pTagFile = getenv("TAGFILE");
    if (pTagFile == NULL)
        pTagFile = "tags";

    if (ExpandPath(pTagFile, Tag, sizeof(Tag)) == -1)
        return 0;
    if (State.GetStrParam(this, Tag, sizeof(Tag)) == 0)
        if (MView->Win->GetFile("Load tags", sizeof(Tag), Tag, HIST_TAGFILES, GF_OPEN) == 0) return 0;

    if (ExpandPath(Tag, FullTag, sizeof(FullTag)) == -1)
        return 0;

    if (!FileExists(FullTag)) {
        Msg(S_INFO, "Tag file '%s' not found.", FullTag);
        return 0;
    }

    return ::TagLoad(FullTag);
}
