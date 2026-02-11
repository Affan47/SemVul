printRegisteredTargetsForVersion() {
  std::vector<std::pair<StringRef, const Target*> > Targets;
  size_t Width = 0;
  for (TargetRegistry::iterator I = TargetRegistry::begin(),
       E = TargetRegistry::end();
       I != E; ++I) {
    Targets.push_back(std::make_pair(I->getName(), &*I));
    Width = std::max(Width, Targets.back().first.size());
  }
  array_pod_sort(Targets.begin(), Targets.end(), TargetArraySortFn);

  raw_ostream &OS = outs();
  OS << "  Registered Targets:\n";
  for (unsigned i = 0, e = Targets.size(); i != e; ++i) {
    OS << "    " << Targets[i].first;
    OS.indent(Width - Targets[i].first.size()) << " - "
      << Targets[i].second->getShortDescription() << '\n';
  }
  if (Targets.empty())
    OS << "    (none)\n";
}
