print() {
  cout << "    ";
  for(int i=0; i<width; i++) {
    printf("%2d", (jMin + i%10));
  }
  cout << endl;
  for(int j=0; j<height; j++) {
    printf("%3d ", j + iMin);
    for(int i=0; i<width; i++) {
      if(data[i+width*j].valid) {
	cout << " " << directionSymbol(data[i+width*j].dir);
      } else {
	cout << " .";
      }
    }
    cout << endl;
  }
}
