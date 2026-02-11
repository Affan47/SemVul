doDisplayTable(std::string* ErrMsg) {
  if (buildPaths(false, ErrMsg))
    return true;
  for (Archive::iterator I = TheArchive->begin(), E = TheArchive->end();
       I != E; ++I ) {
    if (Paths.empty() ||
        (std::find(Paths.begin(), Paths.end(), I->getPath()) != Paths.end())) {
      if (Verbose) {


        if (I->isBitcode())
          outs() << "b";
        else if (I->isCompressed())
          outs() << "Z";
        else
          outs() << " ";
        unsigned mode = I->getMode();
        printMode((mode >> 6) & 007);
        printMode((mode >> 3) & 007);
        printMode(mode & 007);
        outs() << " " << format("%4u", I->getUser());
        outs() << "/" << format("%4u", I->getGroup());
        outs() << " " << format("%8u", I->getSize());
        outs() << " " << format("%20s", I->getModTime().str().substr(4).c_str());
        outs() << " " << I->getPath().str() << "\n";
      } else {
        outs() << I->getPath().str() << "\n";
      }
    }
  }
  if (ReallyVerbose)
    printSymbolTable();
  return false;
}
