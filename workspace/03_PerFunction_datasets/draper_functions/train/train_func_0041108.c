geterrorlist(ErrorList& errlist)
{
    if (!imp->errlist.empty())
    {
        errlist = imp->errlist;
        return true;
    }
    else
    {
        errlist.clear();
        return false;
    }
}
