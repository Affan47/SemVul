MemCheckPostProcess()
{
  if(!this->TestHandler->MemCheck)
    {
    return;
    }
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, this->Index
             << ": process test output now: "
             << this->TestProperties->Name.c_str() << " "
             << this->TestResult.Name.c_str() << std::endl);
  cmCTestMemCheckHandler * handler = static_cast<cmCTestMemCheckHandler*>
    (this->TestHandler);
  switch ( handler->MemoryTesterStyle )
    {
    case cmCTestMemCheckHandler::VALGRIND:
      handler->PostProcessValgrindTest(this->TestResult, this->Index);
      break;
    case cmCTestMemCheckHandler::PURIFY:
      handler->PostProcessPurifyTest(this->TestResult, this->Index);
      break;
    case cmCTestMemCheckHandler::BOUNDS_CHECKER:
      handler->PostProcessBoundsCheckerTest(this->TestResult, this->Index);
      break;
    default:
      break;
    }
}
