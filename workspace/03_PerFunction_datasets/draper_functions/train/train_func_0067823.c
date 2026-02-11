runningSessions()
{


    vector<DBusObject_t> sessions = DBusClientCall1< vector<DBusObject_t> >(*this, "GetSessions")();

    if (sessions.empty()) {
        SE_LOG_SHOW(NULL, "Background sync daemon is idle.");
    } else {
        SE_LOG_SHOW(NULL, "Running session(s): ");


        BOOST_FOREACH(const DBusObject_t &path, sessions) {
            RemoteSession session(*this, path);


            boost::tuple<string, uint32_t, RemoteSession::SourceStatuses_t> status =
                DBusClientCall3<string, uint32_t, RemoteSession::SourceStatuses_t>(session, "GetStatus")();
            std::string syncStatus = boost::get<0>(status);
            if (boost::istarts_with(syncStatus, "running")) {
                Config_t config = DBusClientCall1<Config_t>(session, "GetConfig")(false);
                session.setConfigName(config);

                if (!session.configName().empty()) {
                    SE_LOG_SHOW(NULL, "   %s (%s)", session.configName().c_str(), session.getPath());
                }
            }
        }
    }
}
