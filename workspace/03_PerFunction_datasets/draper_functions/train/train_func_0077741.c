DropTextData(void)
{
    DEBUG(logdebug("Dropping plaintext parts of DB '%s'",_name.c_str()));
    for(SCPSourceList::iterator it = sources.begin(); it != sources.end(); it++)
        Pointers.Delete(*it);
    sources.clear();
    fields.clear();
}
