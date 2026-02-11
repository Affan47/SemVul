DescribeProperty(const wxString& name) const
{
    int msg = SCI_DESCRIBEPROPERTY;
    const long len = SendMsg(msg, (sptr_t)(const char*)wx2sci(name), (uptr_t)NULL);
    if (!len) return wxEmptyString;

    wxMemoryBuffer mbuf(len+1);
    char* buf = (char*)mbuf.GetWriteBuf(len+1);
    SendMsg(msg, (sptr_t)(const char*)wx2sci(name), (uptr_t)buf);
    mbuf.UngetWriteBuf(len);
    mbuf.AppendByte(0);
    return sci2wx(buf);
}
