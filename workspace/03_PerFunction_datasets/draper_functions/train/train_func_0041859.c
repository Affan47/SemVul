KIOSKAuthorizedAction(const KConfigGroup& cfg)
{
    if (!cfg.hasKey("X-KDE-AuthorizeAction")) {
        return true;
    }
    const QStringList list = cfg.readEntry("X-KDE-AuthorizeAction", QStringList());
    for(QStringList::ConstIterator it = list.constBegin();
        it != list.constEnd(); ++it) {
        if (!KAuthorized::authorize((*it).trimmed())) {
            return false;
        }
    }
    return true;
}
