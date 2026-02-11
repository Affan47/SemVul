printweight(std::ostream & o) const{
  for(int i=0; i < size(); i++){
    o << operator[](i)->weight();
    if (i < size()-1) o << " ";
  }
}
