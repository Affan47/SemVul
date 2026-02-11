printableNernst(){
  int result=0;
  for (int i=0; i<size(); i++) {
    if (operator[](i)->typage() != sol &&
	!operator[](i)->iswater() &&
	!operator[](i)->iselectron()) result =1;
  }
  return result;
}
