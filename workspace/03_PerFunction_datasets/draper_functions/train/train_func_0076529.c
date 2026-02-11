renderAsInput(const ArgList &Args, ArgStringList &Output) const {
  if (!getOption().hasNoOptAsInput()) {
    render(Args, Output);
    return;
  }

  Output.append(Values.begin(), Values.end());
}
