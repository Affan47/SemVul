set(const Vector &V){
  int i;

  setsize(V.N);
  for(i = 0; i < N; i++)
    v[i] = V.v[i];
}
