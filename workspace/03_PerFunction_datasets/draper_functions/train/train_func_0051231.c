insertFax(u_int ix, const fxStr& file)
{
    items.insert(FaxItem(send_fax, 0, fxStr::null, file), ix);
}
