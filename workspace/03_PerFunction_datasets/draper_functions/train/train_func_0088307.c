enableAllConnections(bool fEnable) const
{
   for (int i = QUIT + 1; i < m_pActions->size(); i++)
      m_pActions->at(i)->setEnabled(fEnable);
}
