setArenaOptionEnabled(bool option)
{
  kDebug() << option;
  m_arenaAction->setEnabled(option);
  if (option == false)
  {
    emit(arenaStateSignal(false));
  }
}
