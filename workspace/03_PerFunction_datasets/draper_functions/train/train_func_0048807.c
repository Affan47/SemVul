send_email (List * notifList, String& command,
                 String& to, String& listText, int singleSubject)
{
	HtConfiguration* config= HtConfiguration::config();
    String from = "\"";
    from << config->Find("htnotify_webmaster") << "\" <"
         << config->Find("htnotify_sender") << ">";

    String replyto = config->Find("htnotify_replyto");

    if (verbose)
    {
        if (verbose > 1) { cout << endl; }

        cout << "From: " << from << endl;
        cout << "To: " << to << endl;

        if (verbose > 1) { cout << listText; }
    }

    FILE *fileptr;
    if ( (fileptr = popen(command.get(), "w")) != NULL )
    {
        EmailNotification* notif = (EmailNotification*) notifList->Get_First();
        String	out;
        out << "From: " << from << '\n';
        out << "To: " << to << '\n';
        if (replyto.length() > 0)
        { out << "Reply-To: " << replyto << '\n'; }

        if (singleSubject)
        {
            out << "Subject: " << notif->getSubject() << '\n';
        }
        else
        {
            out << "Subject: Web page expiry (" << notif->getSubject() << ", inter alia)\n";
        }

        out << '\n';
        out << preambleText;
        out << listText;
        out << postambleText;
        out << '\n';
        fputs( out.get(), fileptr );
        pclose( fileptr );
    }
    else
    {
        perror( "popen" );
    }
}
