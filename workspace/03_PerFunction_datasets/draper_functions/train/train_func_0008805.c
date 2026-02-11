AddAllArgValues(ArgStringList &Output, OptSpecifier Id0,
                              OptSpecifier Id1, OptSpecifier Id2) const {
  for (auto Arg : filtered(Id0, Id1, Id2)) {
    Arg->claim();
    const auto &Values = Arg->getValues();
    Output.append(Values.begin(), Values.end());
  }
}
