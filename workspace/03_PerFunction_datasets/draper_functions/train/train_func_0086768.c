CeterMessage_conf(std::istream &s)
{

    tString message;
    message.ReadLine( s, true );


    sn_CenterMessage( message );
}
