toplevelMenusEnabled(bool b)
{
    list<QMenu *>::iterator i;
    QMenu *menu;
    for (i=toplevelMenuList.begin(); i != toplevelMenuList.end(); ++i)
    {
        menu = *i;
        menu->setEnabled(b);
    }
}
