AddText(const int length, const wxString& text)
{
    const wxWX2MBbuf buf = (wxWX2MBbuf)wx2sci(text);
    SendMsg(SCI_ADDTEXT, length, (uptr_t)(const char*)buf);
}
