aboutToShowActionMenu()
{
    QMenu *menu = actionToolButton->menu();
    menu->clear();

    QAction *addRule = menu->addAction(tr("Add Custom Rule"));
    connect(addRule, SIGNAL(triggered()), this, SLOT(addCustomRule()));

    QAction *learnRule = menu->addAction(tr("Learn more about writing rules..."));
    connect(learnRule, SIGNAL(triggered()), this, SLOT(learnAboutWritingFilters()));

    menu->addSeparator();

    QModelIndex idx = m_proxyModel->mapToSource(treeView->currentIndex());

    QAction *updateSubscription = menu->addAction(tr("Update Subscription"));
    connect(updateSubscription, SIGNAL(triggered()), this, SLOT(updateSubscription()));
    if (!idx.isValid())
        updateSubscription->setEnabled(false);

    QAction *addSubscription = menu->addAction(tr("Browse Subscriptions..."));
    connect(addSubscription, SIGNAL(triggered()), this, SLOT(browseSubscriptions()));

    menu->addSeparator();

    QAction *removeSubscription = menu->addAction(tr("Remove Subscription"));
    connect(removeSubscription, SIGNAL(triggered()), this, SLOT(removeSubscription()));
    if (!idx.isValid())
        removeSubscription->setEnabled(false);
}
