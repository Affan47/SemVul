main(int argc, char* argv[]) {
    KAboutData about("kcolorutilsdemo", 0, ki18n("kcolorutilsdemo"), "0.1",
                     ki18n("KColorUtils demo/test application"),
                     KAboutData::License_GPL, ki18n("Copyright 2009 Matthew Woehlke"),
                     KLocalizedString(), 0, "mw_triad@users.sourceforge.net");
    about.addAuthor(ki18n("Matthew Woehlke"), KLocalizedString(),
                    "mw_triad@users.sourceforge.net");
    KCmdLineArgs::init(argc, argv, &about);

    KApplication app;
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    Q_UNUSED(args);

    KColorUtilsDemo *d = new KColorUtilsDemo;
    d->show();
    return app.exec();
}
