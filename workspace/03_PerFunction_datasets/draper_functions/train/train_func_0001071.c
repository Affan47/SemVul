computeFSAdditions(StringRef FS, CodeGenOpt::Level OL,
                                      const Triple &TT) {
  std::string FullFS = FS;


  if (TT.getArch() == Triple::ppc64 || TT.getArch() == Triple::ppc64le) {
    if (!FullFS.empty())
      FullFS = "+64bit," + FullFS;
    else
      FullFS = "+64bit";
  }

  if (OL >= CodeGenOpt::Default) {
    if (!FullFS.empty())
      FullFS = "+crbits," + FullFS;
    else
      FullFS = "+crbits";
  }

  if (OL != CodeGenOpt::None) {
    if (!FullFS.empty())
      FullFS = "+invariant-function-descriptors," + FullFS;
    else
      FullFS = "+invariant-function-descriptors";
  }

  return FullFS;
}
