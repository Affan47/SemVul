get_icon_from_wnck(const ProcInfo &info)
{
  Glib::RefPtr<Gdk::Pixbuf> icon;

  IconsForPID::iterator it(this->apps.find(info.pid));

  if (it != this->apps.end())
    icon = it->second;

  return icon;
}
