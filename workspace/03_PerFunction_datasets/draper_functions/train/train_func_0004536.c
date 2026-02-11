setJSPopupBlockerPassivePopup(bool enabled)
{
    d->m_jsPopupBlockerPassivePopup = enabled;

    KConfigGroup cg( KGlobal::config(), "Java/JavaScript Settings");
    cg.writeEntry("PopupBlockerPassivePopup", enabled);
    cg.sync();
}
