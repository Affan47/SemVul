GetTimers(ADDON_HANDLE handle)
{
  if (!mClient)
    return PVR_ERROR_SERVER_ERROR;

  mClient->Lock();

  mClient->SetHandle(handle);
  PVR_ERROR rc = (mClient->GetTimersList() ? PVR_ERROR_NO_ERROR : PVR_ERROR_SERVER_ERROR);

  mClient->Unlock();
  return rc;
}
