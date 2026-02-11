dumpToXML(const Eris::Meta & meta)
{
    cout << "<metaquery>" << endl;
    for(unsigned int S=0; S < meta.getGameServerCount(); ++S)
    {
        const Eris::ServerInfo& sv = meta.getInfoForServer(S);

        cout << "<server status=\"";
        switch (sv.getStatus())
        {
        case Eris::ServerInfo::VALID: cout << "valid"; break;
        case Eris::ServerInfo::TIMEOUT: cout << "timeout"; break;
        case Eris::ServerInfo::QUERYING: cout << "querying"; break;
        default: cout << "failed";
        }
        cout << "\">" << endl;
        cout << "<address>" << sv.getHostname() << "</address>" << endl;
        if(sv.getStatus() == Eris::ServerInfo::VALID)
        {
            cout << "<status>valid</status>" << endl;
            cout << "<name>" << sv.getServername() << "</name>" << endl;
            cout << "<servertype>" << sv.getServer() << "</servertype>" << endl;
            cout << "<ruleset>" << sv.getRuleset() << "</ruleset>" << endl;
            cout << "<uptime>" << timeFormat(sv.getUptime()) << "</uptime>" << endl;
            cout << "<ping>" << sv.getPing() << "</ping>" << endl;
            cout << "<clients>" << sv.getNumClients() << "</clients>" << endl;
			cout << "<builddate>" << sv.getBuildDate() << "</builddate>" << endl;
			cout << "<version>" << sv.getVersion() << "</version>" << endl;
        }
        cout << "</server>" << endl;
    }
    cout << "</metaquery>" << endl;
}
