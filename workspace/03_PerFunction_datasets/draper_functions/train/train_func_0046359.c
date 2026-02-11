InsertString(ExState &State) {
    char strbuf[1024] = "";

    if (State.GetStrParam(View, strbuf, sizeof(strbuf)) == 0) {
        if (View->MView->Win->GetStr("Insert String", sizeof(strbuf), strbuf, HIST_DEFAULT) == 0)
            return 0;
    }
    return InsertString(strbuf, strlen(strbuf));
}
