GetRemainingTimeAllowed()
{
  if (!this->GetHandler("script"))
    {
    return 1.0e7;
    }

  cmCTestScriptHandler* ch
    = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));

  return ch->GetRemainingTimeAllowed();
}
