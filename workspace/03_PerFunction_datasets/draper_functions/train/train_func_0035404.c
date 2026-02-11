UpdateProgress(const char *msg, float prog)
{
  if(this->ProgressCallback && !this->InTryCompile)
    {
    (*this->ProgressCallback)(msg, prog, this->ProgressCallbackClientData);
    return;
    }
}
