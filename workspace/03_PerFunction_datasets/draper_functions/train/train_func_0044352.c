createUpdateMenu()
{
    ActionContainer *menubar = menubarContainer(true);
    Q_ASSERT(menubar);


    ActionContainer *upmenu = actionManager()->createMenu(Constants::M_UPDATE);
    menubar->addMenu(upmenu, Constants::G_UPDATE);
    upmenu->setTranslations(Trans::Constants::M_UPDATE_TEXT);
    upmenu->appendGroup(Id(Constants::G_UPDATE_AVAILABLE));
    upmenu->appendGroup(Id(Constants::G_UPDATE_TODATE));
    upmenu->appendGroup(Id(Constants::G_UPDATE_OTHER));
}
