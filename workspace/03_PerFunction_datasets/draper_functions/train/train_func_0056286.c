filterAcceptsRow(int row, const QModelIndex& p) const
    {
    const QAbstractItemModel* m = this->sourceModel();
    QModelIndex idx = m->index(row, 0, p);


    if(!m->hasChildren(idx))
      {
      bool adv = m->data(idx, QCMakeCacheModel::AdvancedRole).toBool();
      if(!adv || (adv && this->ShowAdvanced))
        {
        return true;
        }
      return false;
      }


    int num = m->rowCount(idx);
    for(int i=0; i<num; i++)
      {
      bool accept = this->filterAcceptsRow(i, idx);
      if(accept)
        {
        return true;
        }
      }
    return false;
    }
}
