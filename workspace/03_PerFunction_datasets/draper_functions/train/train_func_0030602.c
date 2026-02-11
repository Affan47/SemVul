printspecies(std::ostream & o) const{
  bool first=true;
  for(int i=0; i < size(); i++){
    first=operator[](i)->printspecies(o,first);
  }
}
