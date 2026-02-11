saveNsFormat(const std::string& filename)
{
  auto tempfilename = filename;
  tempfilename += "__temp";
  {
    BufferedFile fp{tempfilename.c_str(), BufferedFile::WRITE};
    if(!fp) {
      A2_LOG_ERROR(fmt("Cannot create cookie file %s", filename.c_str()));
      return false;
    }
    for(auto& p : lruTracker_) {
      if(!p.second->writeCookie(fp)) {
        A2_LOG_ERROR(fmt("Failed to save cookies to %s", filename.c_str()));
        return false;
      }
    }
    if(fp.close() == EOF) {
      A2_LOG_ERROR(fmt("Failed to save cookies to %s", filename.c_str()));
      return false;
    }
  }
  if(File(tempfilename).renameTo(filename)) {
    return true;
  } else {
    A2_LOG_ERROR(fmt("Could not rename file %s as %s",
                     tempfilename.c_str(),
                     filename.c_str()));
    return false;
  }
}

}
