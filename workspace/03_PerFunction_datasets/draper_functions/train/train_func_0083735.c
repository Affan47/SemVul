restore(KConfig *config)
{
    KConfigGroup conf(config, "Spelling");
    d->defaultClient = conf.readEntry("defaultClient",
                                      QString());
    d->defaultLanguage = conf.readEntry(
        "defaultLanguage", KGlobal::locale()->language());


    d->checkUppercase = conf.readEntry(
        "checkUppercase", true);

    d->skipRunTogether = conf.readEntry(
        "skipRunTogether", true);

    d->backgroundCheckerEnabled = conf.readEntry(
        "backgroundCheckerEnabled", true);

    d->checkerEnabledByDefault = conf.readEntry(
        "checkerEnabledByDefault", false);

    d->disablePercentage = conf.readEntry("Sonnet_AsYouTypeDisablePercentage", 42);
    d->disableWordCount = conf.readEntry("Sonnet_AsYouTypeDisableWordCount", 100);

    readIgnoreList(config);
}
