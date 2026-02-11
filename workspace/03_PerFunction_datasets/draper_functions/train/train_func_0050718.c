deleteScheme()
{
    if (KMessageBox::questionYesNo(this,
            i18n("Do you really want to delete the scheme %1?\n\
Note that this will not remove any system wide shortcut schemes.", currentScheme())) == KMessageBox::No)
        return;


    QFile::remove(KShortcutSchemesHelper::applicationShortcutSchemeFileName(currentScheme()));


    foreach (KActionCollection *collection, m_dialog->actionCollections())
    {
        const KXMLGUIClient *client = collection->parentGUIClient();
        if (!client)
            continue;
        QFile::remove(KShortcutSchemesHelper::shortcutSchemeFileName(client, currentScheme()));
    }

    m_schemesList->removeItem(m_schemesList->findText(currentScheme()));
    updateDeleteButton();
    emit shortcutsSchemeChanged(currentScheme());
}
