getAllModules(std::vector<Module*>& Modules,
                       std::string* ErrMessage) {

  for (iterator I=begin(), E=end(); I != E; ++I) {
    if (I->isBitcode()) {
      std::string FullMemberName = archPath.str() +
        "(" + I->getPath().str() + ")";
      MemoryBuffer *Buffer =
        MemoryBuffer::getMemBufferCopy(StringRef(I->getData(), I->getSize()),
                                       FullMemberName.c_str());

      Module *M = ParseBitcodeFile(Buffer, Context, ErrMessage);
      delete Buffer;
      if (!M)
        return true;

      Modules.push_back(M);
    }
  }
  return false;
}
