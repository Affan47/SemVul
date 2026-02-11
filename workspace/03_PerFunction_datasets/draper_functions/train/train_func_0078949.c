ReleaseSystemResources()
{
  if (this->Playing || this->Recording)
    {
    this->Stop();
    }

  this->Initialized = 0;
}
