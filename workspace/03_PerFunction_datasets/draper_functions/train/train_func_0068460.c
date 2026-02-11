backupData(const SyncSource::Operations::ConstBackupInfo &oldBackup,
                              const SyncSource::Operations::BackupInfo &newBackup,
                              BackupReport &backupReport)
{
    contactServer();


    ItemCache cache;
    cache.init(oldBackup, newBackup, false);


    const std::string query =
        "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
        "<C:calendar-query xmlns:D=\"DAV:\"\n"
        "xmlns:C=\"urn:ietf:params:xml:ns:caldav\">\n"
        "<D:prop>\n"
        "<D:getetag/>\n"
        "<C:calendar-data/>\n"
        "</D:prop>\n"

        "<C:filter>\n"
        "<C:comp-filter name=\"VCALENDAR\">\n"
        "<C:comp-filter name=\"VEVENT\">\n"
        "</C:comp-filter>\n"
        "</C:comp-filter>\n"
        "</C:filter>\n"
        "</C:calendar-query>\n";
    string data;
    Neon::XMLParser parser;
    parser.initReportParser(boost::bind(&CalDAVSource::backupItem, this,
                                        boost::ref(cache),
                                        _1, _2, boost::ref(data)));
    parser.pushHandler(boost::bind(Neon::XMLParser::accept, "urn:ietf:params:xml:ns:caldav", "calendar-data", _2, _3),
                       boost::bind(Neon::XMLParser::append, boost::ref(data), _2, _3));
    Timespec deadline = createDeadline();
    getSession()->startOperation("REPORT 'full calendar'", deadline);
    while (true) {
        Neon::Request report(*getSession(), "REPORT", getCalendar().m_path, query, parser);
        report.addHeader("Depth", "1");
        report.addHeader("Content-Type", "application/xml; charset=\"utf-8\"");
        if (report.run()) {
            break;
        }
        cache.reset();
    }
    cache.finalize(backupReport);
}
