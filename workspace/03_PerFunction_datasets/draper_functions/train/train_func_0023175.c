Prev()
{
    if (reinterpret_cast<nServerInfo **>(anchor) == &sn_FirstServer)
        return NULL;

    static nServerInfo& info = *this;


    return reinterpret_cast<nServerInfo *>
           ( reinterpret_cast<char*> (anchor) +
             ( reinterpret_cast<char*>( &info ) - reinterpret_cast<char*> (&info.next) )
           );
}
