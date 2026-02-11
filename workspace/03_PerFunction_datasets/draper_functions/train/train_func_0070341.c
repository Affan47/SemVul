FactorWeightProperties(uint64 inprops) {
  uint64 outprops = (kExpanded | kMutable | kError | kAcceptor |
                     kAcyclic | kAccessible | kCoAccessible) & inprops;
  if (inprops & kAccessible)
    outprops |= (kNotAcceptor | kNonIDeterministic | kNonODeterministic |
                 kEpsilons | kIEpsilons | kOEpsilons | kCyclic |
                 kNotILabelSorted | kNotOLabelSorted)
        & inprops;
  return outprops;
}
