intListFromShortcut(const KShortcut &cut)
{
    QList<int> ret;
    ret.append(cut.primary()[0]);
    ret.append(cut.alternate()[0]);
    while (!ret.isEmpty() && ret.last() == 0)
        ret.removeLast();
    return ret;
}
