main(int argc, char ** argv) {

  if(argc!=4) {
    cout << "Checks the array class generating <length> elements between 0 and <maxv> using <seed> as seed for the numbers generation" << endl << endl;
    cout << "usage: " << argv[0] << " <seed> <length> <maxv>" << endl;
    return 0;
  }

  srand(transform(string(argv[1])));
  uint len = transform(string(argv[2]));
  uint maxv = transform(string(argv[3]));


  Array a(len,maxv);
  for(uint i=0;i<len;i++) {
    a.setField(i,rand()%maxv);
  }


  Mapper * mapper = new MapperCont(a, BitSequenceBuilderRG(20));
  Mapper * mapper2 = new MapperNone();
  mapper->use();
  mapper2->use();
  cout << "Test 1 : Wavelet tree with pointers" << endl;
  WaveletTree wt1(a,new wt_coder_huff(a, mapper),new BitSequenceBuilderRG(20), mapper);
  cout << "bs.size() = " << wt1.getSize() << endl;
  testSequence(a, wt1);

  cout << "Test 2 : Wavelet tree without pointers" << endl;
  WaveletTreeNoptrs wt3(a, new BitSequenceBuilderRRR(32), mapper);
  cout << "bs.size() = " << wt3.getSize() << endl;
  testSequence(a, wt3);
  mapper->unuse();
  mapper2->unuse();
  return 0;
}
