List(std::list<FileInfo>& files, DataPoint::DataPointInfoType verb) {
    if (!ftp_active) return DataStatus::NotInitializedError;
    if (reading) return DataStatus::IsReadingError;
    if (writing) return DataStatus::IsWritingError;
    reading = true;
    set_attributes();
    bool more_info = ((verb | INFO_TYPE_NAME) != INFO_TYPE_NAME);
    DataStatus lister_res = lister->retrieve_dir_info(url,!more_info);
    if (!lister_res) {
      logger.msg(VERBOSE, "Failed to obtain listing from FTP: %s", lister_res.GetDesc());
      reading = false;
      return lister_res;
    }
    DataStatus result = DataStatus::Success;
    for (std::list<FileInfo>::iterator i = lister->begin();
         i != lister->end(); ++i) {
      if (i->GetName()[0] != '/')
        i->SetName(url.Path()+'/'+i->GetName());
      std::list<FileInfo>::iterator f =
        files.insert(files.end(), FileInfo(i->GetLastName()));
      if (more_info) {
        DataStatus r = do_more_stat(*i, verb);
        if(!r) {
          if(r == DataStatus::StatError) r = DataStatus(DataStatus::ListError, r.GetDesc());
          result = r;
        }
        f->SetType(i->GetType());
      }
      if (i->CheckSize()) f->SetSize(i->GetSize());
      if (i->CheckModified()) f->SetModified(i->GetModified());
      if (i->CheckCheckSum()) f->SetCheckSum(i->GetCheckSum());
    }
    reading = false;
    return result;
  }
