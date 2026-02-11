close(Ekiga::AudioOutputPS ps)
{
  current_state[ps].opened = false;
  Ekiga::Runtime::run_in_main (boost::bind (&GMAudioOutputManager_null::device_closed_in_main, this, ps, current_state[ps].device));
}
