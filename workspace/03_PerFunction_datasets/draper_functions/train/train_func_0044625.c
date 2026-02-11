init ( const char            * irc,
                    const char            * aim,
                    const char            * icq,
                    const char            * mountPoint )
                                                        throw ( Exception )
{
    this->irc    = irc   ? Util::strDup( irc) : 0;
    this->aim    = aim   ? Util::strDup( aim) : 0;
    this->icq    = icq   ? Util::strDup( icq) : 0;
    this->mountPoint = mountPoint ? Util::strDup( mountPoint ) : 0;
}
