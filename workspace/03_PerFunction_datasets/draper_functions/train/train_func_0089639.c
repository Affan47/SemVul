register_application(pid_t pid, Glib::RefPtr<Gdk::Pixbuf> icon)
{


  if (ProcInfo* info = ProcInfo::find(pid))
    {
      info->set_icon(icon);

      this->apps[pid] = icon;
      procman_debug("WNCK OK for %u", unsigned(pid));
    }
}
