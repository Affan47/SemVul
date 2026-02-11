shortcutFromIntList(const QList<int> &list)
{
    KShortcut ret;
    if (list.count() > 0)
        ret.setPrimary(list[0]);
    if (list.count() > 1)
        ret.setAlternate(list[1]);
    return ret;
}
