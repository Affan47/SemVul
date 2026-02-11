writeErrorMessage()
{
  switch(__type) {
  case asked: {
    fferr(3) << "\nremark: exit command explicitly called\n";
  }
  case normal: {
    fferr(3) << '\n' << __filename << ':' << __lineNumber
	     << ":remark: emitted the following message\n";
    fferr(0) << "error: " << __errorMessage << '\n';
    break;
  }
  case compilation: {
    fferr(0) << "\nline " << __lineNumber << ':' << __errorMessage << '\n';
    break;
  }
  case unexpected: {
    fferr(0) << '\n' << __filename << ':' << __lineNumber << ":\n" << __errorMessage << '\n';
    fferr(0) << "\nUNEXPECTED ERROR: this should not occure, please report it\n";
    fferr(0) << "\nBUG REPORT: Please send bug reports to:\n"
	     << "  ff3d-dev@nongnu.org or freefem@ann.jussieu.fr\n"
	     << "or better, use the Bug Tracking System:\n"
	     << "  http://savannah.nongnu.org/bugs/?group=ff3d\n";
    break;
  }
  default: {
    fferr(0) << __filename << ':' << __lineNumber << ": " << __errorMessage << '\n';
    fferr(0) << __FILE__ << ':' << __LINE__ << ":remark:  error type not implemented!\n";
  }
  }
}
