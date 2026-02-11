ClearSoundDeviceLocatorList(
    SoundSystemInterface::SoundDeviceLocatorList *devices) {
  for (SoundDeviceLocatorList::iterator i = devices->begin();
       i != devices->end();
       ++i) {
    if (*i) {
      delete *i;
    }
  }
  devices->clear();
}
