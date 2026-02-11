setSound(bool neu) {
  if (neu != PrefsDaten::getSound()) {
    if (!neu)
      Sound::setMusic("");
    PrefsDaten::setSound(neu);
    Sound::checkePrefsStatus();
    if (neu)
      Sound::setMusic("cuyo.it");
  }
}
