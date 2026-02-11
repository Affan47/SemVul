GetFile(const char *Prompt, size_t BufLen, char *Str, int HistId, int Flags) {
    if ((HaveGUIDialogs & GUIDLG_FILE) && GUIDialogs)
        return DLGGetFile(this, Prompt, BufLen, Str, Flags);
    else
        return ReadStr(Prompt, BufLen, Str, CompletePath, SelectPathname, HistId);
}
