GetRecordingLastPlayedPosition(const PVR_RECORDING &recording)
{
  if (!mClient)
    return -1;

  return mClient->GetRecordingLastPosition(recording.strRecordingId);
}
