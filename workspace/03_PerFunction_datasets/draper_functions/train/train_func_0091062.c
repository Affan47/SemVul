BrowseSpecialMaster( nServerInfoBase * master, char const * prefix )
{
    sg_currentMaster = master;

    sg_RequestLANcontinuously = false;

    sn_ServerInfoCreator *cback = nServerInfo::SetCreator(&CreateGServer);

    sr_con.autoDisplayAtNewline=true;
    sr_con.fullscreen=true;

#ifndef DEDICATED
    rSysDep::SwapGL();
    rSysDep::ClearGL();
    rSysDep::SwapGL();
    rSysDep::ClearGL();
#endif

    bool to=sr_textOut;
    sr_textOut=true;

    nServerInfo::DeleteAll();
    nServerInfo::GetFromMaster( master, prefix );
    nServerInfo::Save();


    sr_textOut = to;

    tOutput StartHelpTextInternet("$network_master_host_inet_help");
    sg_StartHelpText = &StartHelpTextInternet;
    sg_TalkToMaster = true;

    BrowseServers();

    nServerInfo::Save();

    sg_TalkToMaster = false;

    nServerInfo::SetCreator(cback);

    sg_currentMaster = master;
}
