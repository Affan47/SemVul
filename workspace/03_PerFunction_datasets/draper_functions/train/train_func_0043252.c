printnorm(std::ostream & o) const{
  for(int i=0; i < size(); i++){
    operator[](i)->printnorm(o);
    if (i < size()-1) o << " + ";
  }
}
