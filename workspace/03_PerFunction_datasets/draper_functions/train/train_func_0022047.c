writeInput(){
  for (int i= 0; i < n; i++){
    cout << "h[" << i << "] = ";
    f[i]->write(m);
  }
}
