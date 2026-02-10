RemoveDeadArgumentsFromCallers(Function &Fn)
{


  if (!Fn.isStrongDefinitionForLinker())
    return false;


  if (Fn.hasLocalLinkage() && !Fn.getFunctionType()->isVarArg())
    return false;


  if (Fn.hasFnAttribute(Attribute::Naked))
    return false;

  if (Fn.use_empty())
    return false;

  SmallVector<unsigned, 8> UnusedArgs;
  for (Argument &Arg : Fn.args()) {
    if (Arg.use_empty() && !Arg.hasByValOrInAllocaAttr())
      UnusedArgs.push_back(Arg.getArgNo());
  }

  if (UnusedArgs.empty())
    return false;

  bool Changed = false;

  for (Use &U : Fn.uses()) {
    CallSite CS(U.getUser());
    if (!CS || !CS.isCallee(&U))
      continue;


    for (unsigned I = 0, E = UnusedArgs.size(); I != E; ++I) {
      unsigned ArgNo = UnusedArgs[I];

      Value *Arg = CS.getArgument(ArgNo);
      CS.setArgument(ArgNo, UndefValue::get(Arg->getType()));
      ++NumArgumentsReplacedWithUndef;
      Changed = true;
    }
  }

  return Changed;
}
