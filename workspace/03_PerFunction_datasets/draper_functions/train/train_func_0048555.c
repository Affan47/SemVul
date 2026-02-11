LogMessage(const char* msg)
{
  if (!cmCursesForm::Debug)
    {
    return;
    }

  cmCursesForm::DebugFile << msg << std::endl;
}
