handle_file_system_change_event(
  const Glib::RefPtr<Gio::File> & file, const Glib::RefPtr<Gio::File> &, Gio::FileMonitorEvent event_type)
{
  switch(event_type) {
  case Gio::FILE_MONITOR_EVENT_CHANGED:
  case Gio::FILE_MONITOR_EVENT_DELETED:
  case Gio::FILE_MONITOR_EVENT_CREATED:
  case Gio::FILE_MONITOR_EVENT_MOVED:
    break;
  default:
    return;
  }

  std::string note_id = get_id(file->get_path());

  DBG_OUT("NoteDirectoryWatcher: %s has %d (note_id=%s)", file->get_path().c_str(), int(event_type), note_id.c_str());


  m_lock.lock();
  try {
    std::map<std::string, NoteFileChangeRecord>::iterator record = m_file_change_records.find(note_id);
    if(record == m_file_change_records.end()) {
      m_file_change_records[note_id] = NoteFileChangeRecord();
      record = m_file_change_records.find(note_id);
    }

    if(event_type == Gio::FILE_MONITOR_EVENT_CHANGED) {
      record->second.changed = true;
      record->second.deleted = false;
    }
    else if(event_type == Gio::FILE_MONITOR_EVENT_CREATED) {
      record->second.changed = true;
      record->second.deleted = false;
    }
    else if(event_type == Gio::FILE_MONITOR_EVENT_MOVED) {
      record->second.changed = true;
      record->second.deleted = false;
    }
    else if(event_type == Gio::FILE_MONITOR_EVENT_DELETED) {
      if(!record->second.changed) {
	record->second.deleted = true;
      }
    }

    record->second.last_change = sharp::DateTime::now();
  }
  catch(...)
  {}
  m_lock.unlock();

  Glib::RefPtr<Glib::TimeoutSource> timeout = Glib::TimeoutSource::create(5000);
  timeout->connect(sigc::mem_fun(*this, &NoteDirectoryWatcherApplicationAddin::handle_timeout));
  timeout->attach();
}
