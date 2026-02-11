sourceRowsAboutToBeRemoved(const QModelIndex &source_parent, int start, int end)
{
  Q_Q(KRecursiveFilterProxyModel);

  if (source_parent.isValid() && q->filterAcceptsRow(source_parent.row(), source_parent.parent()))
  {
    invokeRowsAboutToBeRemoved(source_parent, start, end);
    completeRemove = true;
    return;
  }

  bool accepted = false;
  for (int row = start; row <= end; ++row)
  {
    if (q->filterAcceptsRow(row, source_parent))
    {
      accepted = true;
      break;
    }
  }
  if (!accepted)
  {

    ignoreRemove = true;
    return;
  }
  completeRemove = true;
  invokeRowsAboutToBeRemoved(source_parent, start, end);
}
