sn_BanConf(std::istream &s)
{

    tString address;
    s >> address;

    if ( !s.good() && address.Len() < 7 )
    {
        con << "Usage: BAN_IP <ip> <time in minutes (defaults to 60)> <reason>\n";
        return;
    }

    REAL duration = 60;
    s >> duration;


    tString reason;
    std::ws(s);
    if ( s.good() )
    {
        reason.ReadLine(s);
    }


    if ( address.Len() > 4 )
    {
        sn_LookupMachine( address ).Ban( duration * 60, reason );
    }
}
