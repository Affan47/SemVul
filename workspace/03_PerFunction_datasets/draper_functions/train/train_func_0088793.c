getNameWithPrefix(SmallVectorImpl<char> &OutName,
                                const GlobalValue *GV,
                                bool isImplicitlyPrivate) {
  ManglerPrefixTy PrefixTy = Mangler::Default;
  if (GV->hasPrivateLinkage() || isImplicitlyPrivate)
    PrefixTy = Mangler::Private;
  else if (GV->hasLinkerPrivateLinkage() || GV->hasLinkerPrivateWeakLinkage() ||
           GV->hasLinkerPrivateWeakDefAutoLinkage())
    PrefixTy = Mangler::LinkerPrivate;


  if (GV->hasName()) {
    getNameWithPrefix(OutName, GV->getName(), PrefixTy);
  } else {


    unsigned &ID = AnonGlobalIDs[GV];
    if (ID == 0) ID = NextAnonGlobalID++;


    getNameWithPrefix(OutName, "__unnamed_" + Twine(ID), PrefixTy);
  }


  if (Context.getAsmInfo().hasMicrosoftFastStdCallMangling()) {
    if (const Function *F = dyn_cast<Function>(GV)) {
      CallingConv::ID CC = F->getCallingConv();


      if (CC == CallingConv::X86_FastCall) {
        if (OutName[0] == '_')
          OutName[0] = '@';
        else
          OutName.insert(OutName.begin(), '@');
      }


      FunctionType *FT = F->getFunctionType();
      if ((CC == CallingConv::X86_FastCall || CC == CallingConv::X86_StdCall) &&

          (!FT->isVarArg() || FT->getNumParams() == 0 ||
           (FT->getNumParams() == 1 && F->hasStructRetAttr())))
        AddFastCallStdCallSuffix(OutName, F, TD);
    }
  }
}
