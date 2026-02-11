updateForeground(unsigned long oldfg_)
{
  MSMenuItem::updateForeground(oldfg_);
  if (cascadeMenu()!=0&&cascadeMenu()->foreground()==oldfg_)
  {
     cascadeMenu()->foreground(foreground());
  }
}
