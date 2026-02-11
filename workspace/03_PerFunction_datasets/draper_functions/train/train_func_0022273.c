DoBranch(HBranch* instr) {
  HValue* v = instr->value();
  if (v->EmitAtUses()) {
    ASSERT(v->IsConstant());
    ASSERT(!v->representation().IsDouble());
    HBasicBlock* successor = HConstant::cast(v)->ToBoolean()
        ? instr->FirstSuccessor()
        : instr->SecondSuccessor();
    return new LGoto(successor->block_id());
  }
  return AssignEnvironment(new LBranch(UseRegister(v)));
}
