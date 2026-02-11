properties() const
{
  QCMakePropertyList props;

  if(!this->rowCount())
    {
    return props;
    }

  QList<QModelIndex> idxs;
  idxs.append(this->index(0,0));


  while(!idxs.isEmpty())
  {
    QModelIndex idx = idxs.last();
    if(this->hasChildren(idx) && this->rowCount(idx))
    {
      idxs.append(this->index(0,0, idx));
    }
    else
    {
      if(!data(idx, GroupRole).toInt())
      {

        QCMakeProperty prop;
        this->getPropertyData(idx, prop);
        props.append(prop);
      }


      while(!idxs.isEmpty() && (
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0) && QT_VERSION < QT_VERSION_CHECK(5, 1, 0)
        (idxs.last().row()+1) >= rowCount(idxs.last().parent()) ||
#endif
        !idxs.last().sibling(idxs.last().row()+1, 0).isValid()))
      {
        idxs.removeLast();
      }
      if(!idxs.isEmpty())
      {
        idxs.last() = idxs.last().sibling(idxs.last().row()+1, 0);
      }
    }
  }

  return props;
}
