createMenu(const QModelIndex &parent, int max, QMenu *parentMenu, QMenu *menu)
{
    if (!menu) {
        QVariant v;
        v.setValue(parent);

        QString title = parent.data().toString();
        ModelMenu *modelMenu = createBaseMenu();

        disconnect(modelMenu, SIGNAL(triggered(QAction*)),
                   modelMenu, SLOT(actionTriggered(QAction*)));
        modelMenu->setTitle(title);
        QIcon icon = qvariant_cast<QIcon>(parent.data(Qt::DecorationRole));
        modelMenu->setIcon(icon);
        parentMenu->addMenu(modelMenu)->setData(v);
        modelMenu->setRootIndex(parent);
        modelMenu->setModel(m_model);
        return;
    }

    if (!m_model)
        return;

    int end = m_model->rowCount(parent);
    if (max != -1)
        end = qMin(max, end);


    for (int i = 0; i < end; ++i) {
        QModelIndex idx = m_model->index(i, 0, parent);
        if (m_model->hasChildren(idx)) {
            createMenu(idx, -1, menu);
        } else {
            if (m_separatorRole != 0
                && idx.data(m_separatorRole).toBool())
                addSeparator();
            else
                menu->addAction(makeAction(idx));
        }
        if (menu == this && i == m_firstSeparator - 1)
            addSeparator();
    }
}
