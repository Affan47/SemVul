readMatrix(CFileLineReader & cfile,
		     unsigned int & row, unsigned int & col) {
  if(!cfile)
    throw SetupException()
      << "SusyBase::readMatrix() - The input stream is in a bad state."
      << Exception::runerror;
  unsigned int rowmax(0), colmax(0);
  MixingVector values;
  while(cfile.readline()) {
    string line = cfile.getline();

    if(line[0] == '#') continue;

    if( line[0] == 'B' || line[0] == 'b' ||
	line[0] == 'D' || line[0] == 'd' ||
	line[0] == '<' ) {
      cfile.resetline();
      break;
    }
    istringstream is(line);
    unsigned int index1, index2;
    double real(0.), imag(0.);
    is >> index1 >> index2 >> real >> imag;
    values.push_back(MixingElement(index1,index2,Complex(real, imag)));
    if(index1 > rowmax) rowmax = index1;
    if(index2 > colmax) colmax = index2;

  }
  col=colmax;
  row=rowmax;
  return values;
}
