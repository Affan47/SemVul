createHelpMenu()
{
    ActionContainer *menubar = menubarContainer(true);
    Q_ASSERT(menubar);

    ActionContainer *m = actionManager()->createMenu(Constants::M_HELP);
    menubar->addMenu(m, Constants::G_HELP);
    m->setTranslations(Trans::Constants::M_ABOUT_TEXT);
    m->appendGroup(Id(Constants::G_HELP_HELP));
    m->appendGroup(Id(Constants::G_UPDATE));
    m->appendGroup(Id(Constants::G_HELP_DEBUG));
    m->appendGroup(Id(Constants::G_HELP_OTHER));
    m->appendGroup(Id(Constants::G_HELP_DATABASES));
    m->appendGroup(Id(Constants::G_HELP_ABOUT));

    ActionContainer *mdb = actionManager()->createMenu(Constants::M_HELP_DATABASES);
    m->addMenu(mdb, Constants::G_HELP_DATABASES);
    mdb->appendGroup(Id(Constants::G_HELP_DATABASES));
    mdb->setTranslations(Trans::Constants::ABOUTDATABASES_TEXT);
}
