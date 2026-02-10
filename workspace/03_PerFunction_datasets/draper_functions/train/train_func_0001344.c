appliFontToViews(const QFont &font)
{
    QList<Templates::TemplatesView *> allViews = Core::ICore::instance()->mainWindow()->findChildren<Templates::TemplatesView *>();
    for(int i = 0; i < allViews.count(); ++i) {
        allViews.at(i)->setFont(font);
    }
}
