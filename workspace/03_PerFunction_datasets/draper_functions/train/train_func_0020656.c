initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);
    Q_ASSERT_X(userModel()->hasCurrentUser(), "UserManagerMainWindow", "NO CURRENT USER");
    if (!userModel()->hasCurrentUser())
        return false;

    Q_ASSERT(actionManager());
    Q_ASSERT(contextManager());


    createFileMenu();
    createEditMenu();
    createFormatMenu();
    createConfigurationMenu();
    createHelpMenu();

    Core::MainWindowActions actions;
    actions.setFileActions(
            Core::MainWindowActions::A_FilePrint |
            Core::MainWindowActions::A_FilePrintPreview |
            Core::MainWindowActions::A_FileQuit
            );

    actions.setConfigurationActions(
            Core::MainWindowActions::A_AppPreferences |

            Core::MainWindowActions::A_PluginsPreferences |
            Core::MainWindowActions::A_LanguageChange
            );

    actions.setHelpActions(
            Core::MainWindowActions::A_AppAbout |
            Core::MainWindowActions::A_PluginsAbout |
            Core::MainWindowActions::A_AppHelp |
            Core::MainWindowActions::A_DebugDialog |
            Core::MainWindowActions::A_AppGoToWebSite
                );

    actions.createEditActions(true);
    createActions(actions);
    if (!m_Widget->initialize())
        return false;
    return true;
}
