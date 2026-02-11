main(int argc, char *argv[])
{
    KAboutData aboutData("kollision", 0, ki18n("Kollision"),
                         "0.1", ki18n("KDE collision game"), KAboutData::License_GPL,
                         ki18n("(c) 2007 Paolo Capriotti"), KLocalizedString(), "http://games.kde.org/kollision");
    aboutData.addAuthor(ki18n("Paolo Capriotti"), KLocalizedString(), "p.capriotti@gmail.com");
    aboutData.addAuthor(ki18n("Dmitry Suzdalev"), KLocalizedString(), "dimsuz@gmail.com");
    aboutData.addCredit(ki18n("Matteo Guarnieri"), ki18n("Original idea"));
    aboutData.addCredit(ki18n("Brian Croom"), ki18n("Port to use KGameRenderer"));

    KCmdLineArgs::init(argc, argv, &aboutData);

    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;
    KGlobal::locale()->insertCatalog( QLatin1String( "libkdegames" ));

    MainWindow* window = new MainWindow;
    window->show();

    return app.exec();
}
