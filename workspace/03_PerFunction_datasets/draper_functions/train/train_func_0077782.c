setFilterBehavior(FilterBehavior behavior)
{
    Q_D(KSelectionProxyModel);

    beginResetModel();

    d->m_filterBehavior = behavior;

    switch (behavior) {
    case SubTrees: {
        d->m_omitChildren = false;
        d->m_omitDescendants = false;
        d->m_startWithChildTrees = false;
        d->m_includeAllSelected = false;
        break;
    }
    case SubTreeRoots: {
        d->m_omitChildren = true;
        d->m_startWithChildTrees = false;
        d->m_includeAllSelected = false;
        break;
    }
    case SubTreesWithoutRoots: {
        d->m_omitChildren = false;
        d->m_omitDescendants = false;
        d->m_startWithChildTrees = true;
        d->m_includeAllSelected = false;
        break;
    }
    case ExactSelection: {
        d->m_omitChildren = true;
        d->m_startWithChildTrees = false;
        d->m_includeAllSelected = true;
        break;
    }
    case ChildrenOfExactSelection: {
        d->m_omitChildren = false;
        d->m_omitDescendants = true;
        d->m_startWithChildTrees = true;
        d->m_includeAllSelected = true;
        break;
    }
    }
    d->resetInternalData();
    d->selectionChanged(d->m_selectionModel.data()->selection(), QItemSelection());

    endResetModel();
}
