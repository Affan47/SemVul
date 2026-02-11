TidyLandingPads(DenseMap<MCSymbol*, uintptr_t> *LPMap) {
  for (unsigned i = 0; i != LandingPads.size(); ) {
    LandingPadInfo &LandingPad = LandingPads[i];
    if (LandingPad.LandingPadLabel &&
        !LandingPad.LandingPadLabel->isDefined() &&
        (!LPMap || (*LPMap)[LandingPad.LandingPadLabel] == 0))
      LandingPad.LandingPadLabel = nullptr;


    if (!LandingPad.LandingPadLabel && LandingPad.LandingPadBlock) {
      LandingPads.erase(LandingPads.begin() + i);
      continue;
    }

    for (unsigned j = 0, e = LandingPads[i].BeginLabels.size(); j != e; ++j) {
      MCSymbol *BeginLabel = LandingPad.BeginLabels[j];
      MCSymbol *EndLabel = LandingPad.EndLabels[j];
      if ((BeginLabel->isDefined() ||
           (LPMap && (*LPMap)[BeginLabel] != 0)) &&
          (EndLabel->isDefined() ||
           (LPMap && (*LPMap)[EndLabel] != 0))) continue;

      LandingPad.BeginLabels.erase(LandingPad.BeginLabels.begin() + j);
      LandingPad.EndLabels.erase(LandingPad.EndLabels.begin() + j);
      --j, --e;
    }


    if (LandingPads[i].BeginLabels.empty()) {
      LandingPads.erase(LandingPads.begin() + i);
      continue;
    }


    if (!LandingPad.LandingPadBlock ||
        (LandingPad.TypeIds.size() == 1 && !LandingPad.TypeIds[0]))
      LandingPad.TypeIds.clear();
    ++i;
  }
}
