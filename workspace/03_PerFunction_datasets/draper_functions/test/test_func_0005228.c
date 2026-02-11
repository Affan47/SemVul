CreateDeoptimize(
    HDeoptimize::UseEnvironment has_uses) {
  ASSERT(HasEnvironment());
  if (has_uses == HDeoptimize::kNoUses) return new(zone()) HDeoptimize(0);

  HEnvironment* environment = last_environment();
  HDeoptimize* instr = new(zone()) HDeoptimize(environment->length());
  for (int i = 0; i < environment->length(); i++) {
    HValue* val = environment->values()->at(i);
    instr->AddEnvironmentValue(val);
  }

  return instr;
}
