set_display_info (const DisplayInfo & _display_info)
{
  PWaitAndSignal m(core_mutex);

  for (std::set<VideoOutputManager *>::iterator iter = managers.begin ();
       iter != managers.end ();
       iter++) {
    (*iter)->set_display_info (_display_info);
  }
}
