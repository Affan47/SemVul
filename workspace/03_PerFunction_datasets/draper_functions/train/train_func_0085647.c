find_action_by_name(const std::string & n) const
  {
    Glib::ListHandle<Glib::RefPtr<Gtk::Action> > actions = m_main_window_actions->get_actions();
    for(Glib::ListHandle<Glib::RefPtr<Gtk::Action> >::const_iterator iter2(actions.begin());
        iter2 != actions.end(); ++iter2) {
      if((*iter2)->get_name() == n) {
        return *iter2;
      }
    }
    DBG_OUT("%s not found", n.c_str());
    return Glib::RefPtr<Gtk::Action>();
  }
