activatedMenu(const KFileItem &item, const QPoint &pos)
{
    Q_UNUSED(item);
    updateSelectionDependentActions();

    d->newFileMenu->setPopupFiles(url());
    d->newFileMenu->setViewShowsHiddenFiles(showHiddenFiles());
    d->newFileMenu->checkUpToDate();

    emit contextMenuAboutToShow( item, d->actionMenu->menu() );

    d->actionMenu->menu()->exec(pos);
}
