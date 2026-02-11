ExtractEventDetectionFlag(Acquisition::Pointer output, std::istringstream* iss, const std::string& label, const std::string& context)
  {
    iss->clear();
    std::string buf;
    *iss >> buf;
    *iss >> buf;
    double frame;
    do
    {
      *iss >> frame;
      for (Acquisition::EventIterator it = output->BeginEvent() ; it != output->EndEvent() ; ++it)
      {
        if (((*it)->GetLabel().compare(label) == 0)
            && ((*it)->GetContext().compare(context) == 0)
            && ((*it)->GetFrame() == static_cast<int>(frame) + output->GetFirstFrame()))
        {
          (*it)->SetDetectionFlags(Event::FromForcePlatform);
          break;
        }
      }
    }
    while(!iss->eof());
  }
