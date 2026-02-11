setMenuEntries(const KAccelStringList &list)
{
  uint cnt = 0;
  foreach (QAction *maction, m_popup->actions())
  {
    if (maction->isSeparator())
      continue;

    if (KAcceleratorManagerPrivate::checkChange(list[cnt]))
        maction->setText(list[cnt].accelerated());
    cnt++;
  }
}
