IssueMessage(cmake::MessageType t, std::string const& text,
                         cmListFileBacktrace const& backtrace)
{
  cmOStringStream msg;
  bool isError = false;

  if(t == cmake::FATAL_ERROR)
    {
    isError = true;
    msg << "CMake Error";
    }
  else if(t == cmake::INTERNAL_ERROR)
    {
    isError = true;
    msg << "CMake Internal Error (please report a bug)";
    }
  else
    {
    msg << "CMake Warning";
    if(t == cmake::AUTHOR_WARNING)
      {

      cmCacheManager::CacheIterator it = this->CacheManager
        ->GetCacheIterator("CMAKE_SUPPRESS_DEVELOPER_WARNINGS");
      if(!it.IsAtEnd() && it.GetValueAsBool())
        {
        return;
        }
      msg << " (dev)";
      }
    }


  cmListFileBacktrace::const_iterator i = backtrace.begin();
  if(i != backtrace.end())
    {
    cmListFileContext const& lfc = *i;
    msg << (lfc.Line? " at ": " in ") << lfc;
    ++i;
    }


  {
  msg << ":\n";
  cmDocumentationFormatterText formatter;
  formatter.SetIndent("  ");
  formatter.PrintFormatted(msg, text.c_str());
  }


  if(i != backtrace.end())
    {
    msg << "Call Stack (most recent call first):\n";
    while(i != backtrace.end())
      {
      cmListFileContext const& lfc = *i;
      msg << "  " << lfc << "\n";
      ++i;
      }
    }


  if(t == cmake::AUTHOR_WARNING)
    {
    msg <<
      "This warning is for project developers.  Use -Wno-dev to suppress it.";
    }


  msg << "\n";


  if(isError)
    {
    cmSystemTools::SetErrorOccured();
    cmSystemTools::Message(msg.str().c_str(), "Error");
    }
  else
    {
    cmSystemTools::Message(msg.str().c_str(), "Warning");
    }
}
