kdemain(int argc, char *argv[])
{
     KAboutData aboutData( "kded" ,
        "kdelibs4", ki18n("KDE Daemon"),
        KDE_VERSION_STRING,
        ki18n("KDE Daemon - triggers Sycoca database updates when needed"));

     KCmdLineOptions options;
     options.add("check", ki18n("Check Sycoca database only once"));

     KCmdLineArgs::init(argc, argv, &aboutData);

     KUniqueApplication::addCmdLineOptions();

     KCmdLineArgs::addCmdLineOptions( options );


     putenv(qstrdup("SESSION_MANAGER="));


     KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

     KComponentData componentData(&aboutData);
     KSharedConfig::Ptr config = componentData.config();

     KConfigGroup cg(config, "General");
     if (args->isSet("check"))
     {

        KApplication app;
        checkStamps = cg.readEntry("CheckFileStamps", true);
        runBuildSycoca();
        runKonfUpdate();
        return 0;
     }

     if (!KUniqueApplication::start())
     {
        fprintf(stderr, "KDE Daemon (kded) already running.\n");
        return 0;
     }


     HostnamePollInterval = cg.readEntry("HostnamePollInterval", 5000);
     bCheckSycoca = cg.readEntry("CheckSycoca", true);
     bCheckUpdates = cg.readEntry("CheckUpdates", true);
     bCheckHostname = cg.readEntry("CheckHostname", true);
     checkStamps = cg.readEntry("CheckFileStamps", true);
     delayedCheck = cg.readEntry("DelayedCheck", false);

     Kded *kded = new Kded();

#ifndef _WIN32_WCE
     KDE_signal(SIGTERM, sighandler);
#endif
     KDE_signal(SIGHUP, sighandler);
     KDEDApplication k;
     k.setQuitOnLastWindowClosed(false);

     KCrash::setFlags(KCrash::AutoRestart);


     kded->moveToThread( k.thread() );

     int result = k.exec();

     delete kded;

     return result;
}
