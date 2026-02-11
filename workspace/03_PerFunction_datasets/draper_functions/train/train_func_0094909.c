setsize(int vN){
  if(vN < 0){
    cerr << "vector dimension of " << vN << " invalid" << endl;
    exit(1);
  }

  N = vN;
  if(N == 0)
    v = NULL;
  else{
    v = new double[N];
    if(!v){
      cerr << "not enough memory to allocate vector of size " << N << endl;
      exit(1);
    }
  }

  int i;
  for(i = 0; i < N; i++)
    v[i] = 0;
}
