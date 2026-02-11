load_notebooks()
    {
      Gtk::TreeIter iter;
      std::list<Tag::Ptr> tags;
      ITagManager::obj().all_tags(tags);
      for(std::list<Tag::Ptr>::const_iterator tag_iter = tags.begin();
          tag_iter != tags.end(); ++tag_iter) {

        const Tag::Ptr & tag(*tag_iter);

        if (!tag->is_system()
            || !Glib::str_has_prefix(tag->name(),
                                     std::string(Tag::SYSTEM_TAG_PREFIX)
                                     + Notebook::NOTEBOOK_TAG_PREFIX)) {
          continue;
        }
        Notebook::Ptr notebook(new Notebook(m_note_manager, tag));
        iter = m_notebooks->append ();
        iter->set_value(0, notebook);
        m_notebookMap [notebook->get_normalized_name()] = iter;
      }
    }
