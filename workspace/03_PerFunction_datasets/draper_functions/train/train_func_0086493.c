dataBaseOutput(ofstream & output,bool header,bool create) const {
  if(header) {
    output << "update decayers set parameters=\"";
  }
  if(create) {
    output << "create Herwig::WeakDecayCurrent " << name() << " \n";
  }
  for(unsigned int ix=0;ix<_quark.size();++ix) {
    if(ix<_numbermodes) {
      output << "newdef " << name() << ":Quark "
	     << ix << "  " << _quark[ix]     << endl;
      output << "newdef " << name() << ":AntiQuark "
	     << ix << "  " << _antiquark[ix] << endl;
    }
    else {
      output << "insert "  << name() << ":Quark "
	     << ix << "  " << _quark[ix]     << endl;
      output << "insert "  << name() << ":AntiQuark "
	     << ix << "  " << _antiquark[ix] << endl;
    }
  }
  if(header) {
    output << "\n\" where BINARY ThePEGName=\"" << fullName() << "\";" << endl;
  }
}
