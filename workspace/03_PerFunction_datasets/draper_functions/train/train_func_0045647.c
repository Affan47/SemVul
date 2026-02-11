isSoundEnabled() const
{
  return !actionCollection()->action(QLatin1String( "speech_no_sound" ))->isChecked();
}
