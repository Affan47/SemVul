getPersonalityIndex() const {
  const Function* Personality = NULL;


  for (unsigned i = 0; i != LandingPads.size(); ++i)
    if (LandingPads[i].Personality) {
      Personality = LandingPads[i].Personality;
      break;
    }

  for (unsigned i = 0; i < Personalities.size(); ++i) {
    if (Personalities[i] == Personality)
      return i;
  }


  return 0;
}
