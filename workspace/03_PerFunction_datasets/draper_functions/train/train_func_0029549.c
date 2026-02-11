slotViewNoBackground(bool toggle)
{
  if (activeDocument() && toggle)
  {
    activeDocument()->setBackground(BlankBackground);

    DefaultSettings::instance().setViewBackground(BlankBackground);
  }
}
