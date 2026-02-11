writeDegrees(){
  cout << "\n";
  cout << " Matrix Degrees \n";
  for (int i = 0; i < n; i++){
    cout << "Row " << i << " : " << degrees[3*i] << "  " << degrees[3*i+1] << "  " << degrees[3*i+2] << endl;
  }
}
