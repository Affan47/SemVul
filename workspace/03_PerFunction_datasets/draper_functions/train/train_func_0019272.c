main(int argc, char ** argv) {

  if(argc!=4) {
    cout << "Checks the bitsequence classes generating <length> bitmaps with density <dens> using <seed> as seed for the numbers generation" << endl << endl;
    cout << "usage: " << argv[0] << " <seed> <length> <dens>" << endl;
    return 0;
  }

  srand(transform(string(argv[1])));
  uint len = transform(string(argv[2]));
  uint dens = transform(string(argv[3]));

  uint act_dens = 0;
  BitString a(len);
  while(act_dens < dens) {
      size_t pos = rand()%len;
      if(!a[pos]) {
          act_dens++;
          a.setBit(pos,true);
      }
  }

  BitSequenceRG bsRG(a,20);
  BitSequence * s = saveLoad(&bsRG);
  if(!testBitSequence(a,s)) {
      cerr << "ERROR TESTING BitSequenceRG" << endl;
      return -1;
  }
	cout << "RG OK\n" << endl;
  delete (BitSequenceRG *)s;

	BitSequenceDArray bsDArray(a);
	s = saveLoad(&bsDArray);
	if(!testBitSequence(a,s)) {
		cerr << "ERROR TESTING BitSequenceDArray" << endl;
		return -1;
	}
	cout << "DArray OK\n" << endl;
	delete (BitSequenceDArray *)s;

	BitSequenceSDArray bsSDArray(a);
  s = saveLoad(&bsSDArray);
  if(!testBitSequence(a,s)) {
      cerr << "ERROR TESTING BitSequenceSDArray" << endl;
      return -1;
  }
	cout << "SDArray OK\n" << endl;
  delete (BitSequenceSDArray *)s;

	BitSequenceRRR bsRRR(a,33);
  s = saveLoad(&bsRRR);
  if(!testBitSequence(a,s)) {
      cerr << "ERROR TESTING BitSequenceRRR" << endl;
      return -1;
  }
	cout << "RRR OK\n" << endl;
  delete (BitSequenceRRR *)s;
  return 0;
}
