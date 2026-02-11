CreateAcquisitionIO(const std::string& filename, OpenMode mode)
  {
    AcquisitionFileIO::Pointer io;
    if (mode == ReadMode)
    {
      for (AcquisitionFileIOHandles::ConstIterator it = AcquisitionFileIOFactory::GetInfoIOs()->list.begin() ; it != AcquisitionFileIOFactory::GetInfoIOs()->list.end() ; ++it)
      {
        if ((*it)->HasReadOperation() && (io = (*it)->GetFileIO())->CanReadFile(filename))
          return io;
      }
    }
    else
    {
      for (AcquisitionFileIOHandles::ConstIterator it = AcquisitionFileIOFactory::GetInfoIOs()->list.begin() ; it != AcquisitionFileIOFactory::GetInfoIOs()->list.end() ; ++it)
      {
        if ((*it)->HasWriteOperation() && (io = (*it)->GetFileIO())->CanWriteFile(filename))
          return io;
      }
    }
    return AcquisitionFileIO::Pointer();
  }
