getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;


  bool SoftFloat =
      F.hasFnAttribute("use-soft-float") &&
      F.getFnAttribute("use-soft-float").getValueAsString() == "true";


  if (SoftFloat)
    FS += FS.empty() ? "+soft-float" : ",+soft-float";

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {


    resetTargetOptions(F);
    I = llvm::make_unique<X86Subtarget>(TargetTriple, CPU, FS, *this,
                                        Options.StackAlignmentOverride);
  }
  return I.get();
}
