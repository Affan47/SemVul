matches(const coverage::FunctionRecord &Function) {
  for (const auto &Filter : Filters) {
    if (Filter->matches(Function))
      return true;
  }
  return false;
}
