shortcutSchemeFileName(const KXMLGUIClient *client, const QString &schemeName)
{
    return KStandardDirs::locateLocal("data",
        client->componentData().componentName() + '/' +
        client->componentData().componentName() + schemeName + "shortcuts.rc" );
}
