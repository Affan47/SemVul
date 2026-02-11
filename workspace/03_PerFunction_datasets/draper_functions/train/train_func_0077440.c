OpenPlaybackDevice(
      const SoundDeviceLocator *device,
      const OpenParams &params) {
  return new NullSoundOutputStream();
}
