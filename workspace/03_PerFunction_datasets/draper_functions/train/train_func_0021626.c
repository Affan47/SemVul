printLocation(llvm::Instruction *I, bool a, bool b) {
    if (MDNode *N = I->getMetadata("dbg")) {
	DILocation Loc(N);
	errs() << Loc.getFilename() << ":" << Loc.getLineNumber();
	if (unsigned Col = Loc.getColumnNumber()) {
  	    errs() << ":" << Col;
  	}
  	errs() << ": ";
  	return;
    }
    errs() << *I << ":\n";
}
