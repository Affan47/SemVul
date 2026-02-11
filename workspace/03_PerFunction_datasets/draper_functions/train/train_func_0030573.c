addCurrentFnArgument(const MachineFunction *MF,
                                      DbgVariable *Var, LexicalScope *Scope) {
  if (!LScopes.isCurrentFunctionScope(Scope))
    return false;
  DIVariable DV = Var->getVariable();
  if (DV.getTag() != dwarf::DW_TAG_arg_variable)
    return false;
  unsigned ArgNo = DV.getArgNumber();
  if (ArgNo == 0)
    return false;

  size_t Size = CurrentFnArguments.size();
  if (Size == 0)
    CurrentFnArguments.resize(MF->getFunction()->arg_size());


  if (ArgNo > Size)
    CurrentFnArguments.resize(ArgNo * 2);
  CurrentFnArguments[ArgNo - 1] = Var;
  return true;
}
