doCommand()
{
  m_model->layoutAboutToBeChanged();
  QModelIndexList oldList;

  foreach(const PersistentChange &change, m_changes)
  {
    const IndexFinder oldFinder(m_model, change.oldPath);
    oldList << oldFinder.getIndex();
  }

  bool blocked = m_model->blockSignals(true);
  m_model->clear();
  if (!m_treeString.isEmpty())
  {
    ModelInsertCommand *ins = new ModelInsertCommand(m_model);
    ins->setStartRow(0);
    ins->interpret(m_treeString);
    ins->doCommand();
  }

  QModelIndexList newList;
  foreach(const PersistentChange &change, m_changes)
  {
    const IndexFinder newFinder(m_model, change.newPath);
    newList << newFinder.getIndex();
  }
  m_model->changePersistentIndexList(oldList, newList);

  m_model->blockSignals(blocked);
  m_model->layoutChanged();
}
