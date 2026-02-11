remove_tag (const Tag::Ptr & tag)
  {
    if (!tag)
      throw sharp::Exception ("TagManager.RemoveTag () called with a null tag");

    if(tag->is_property() || tag->is_system()){

      Glib::Mutex::Lock lock(m_locker);

      m_internal_tags.erase(tag->normalized_name());
    }
    bool tag_removed = false;
    std::map<std::string, Gtk::TreeIter>::iterator map_iter;
    map_iter = m_tag_map.find(tag->normalized_name());
    if (map_iter != m_tag_map.end()) {

      Glib::Mutex::Lock lock(m_locker);

      map_iter = m_tag_map.find(tag->normalized_name());
      if (map_iter != m_tag_map.end()) {
        Gtk::TreeIter iter = map_iter->second;
        if (!m_tags->erase(iter)) {
          DBG_OUT("TagManager: Removed tag: %s", tag->normalized_name().c_str());
        }
        else {

          DBG_OUT("TagManager: Call to remove tag from ListStore failed: %s", tag->normalized_name().c_str());
        }

        m_tag_map.erase(map_iter);
        DBG_OUT("Removed TreeIter from tag_map: %s", tag->normalized_name().c_str());
        tag_removed = true;

        std::list<Note*> notes;
        tag->get_notes(notes);
        for(std::list<Note*>::const_iterator note_iter = notes.begin();
            note_iter != notes.end(); ++note_iter) {
          (*note_iter)->remove_tag(tag);
        }
      }
    }

    if (tag_removed) {
      m_signal_tag_removed(tag->normalized_name());
    }
  }
