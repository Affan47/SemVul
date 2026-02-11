open (unsigned channels, unsigned samplerate, unsigned bits_per_sample)
{
  PTRACE(4, "GMAudioInputManager_ptlib\tOpening Device " << current_state.device);
  PTRACE(4, "GMAudioInputManager_ptlib\tOpening Device with " << channels << "-" << samplerate << "/" << bits_per_sample);

  current_state.channels        = channels;
  current_state.samplerate      = samplerate;
  current_state.bits_per_sample = bits_per_sample;

  input_device = PSoundChannel::CreateOpenedChannel (current_state.device.source,
#ifdef WIN32
                                                     utf2codepage (current_state.device.name),
#else
                                                     current_state.device.name,
#endif
                                                     PSoundChannel::Recorder,
                                                     channels,
                                                     samplerate,
                                                     bits_per_sample);

  Ekiga::AudioInputErrorCodes error_code = Ekiga::AI_ERROR_NONE;
  if (!input_device)
    error_code = Ekiga::AI_ERROR_DEVICE;

  if (error_code != Ekiga::AI_ERROR_NONE) {
    PTRACE(1, "GMAudioInputManager_ptlib\tEncountered error " << error_code << " while opening device ");
    Ekiga::Runtime::run_in_main (boost::bind (&GMAudioInputManager_ptlib::device_error_in_main, this, current_state.device, error_code));
    return false;
  }

  unsigned volume;
  input_device->GetVolume (volume);
  current_state.opened = true;

  Ekiga::AudioInputSettings settings;
  settings.volume = volume;
  settings.modifyable = true;
  Ekiga::Runtime::run_in_main (boost::bind (&GMAudioInputManager_ptlib::device_opened_in_main, this, current_state.device, settings));

  return true;
}
