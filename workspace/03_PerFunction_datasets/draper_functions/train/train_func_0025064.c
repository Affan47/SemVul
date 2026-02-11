operator[](unsigned int n) {
  if(n>=items_.size()) return NULL;
  std::list<Item*>::iterator i = items_.begin();
  for(;n && (i!=items_.end());--n,++i){};
  if(i==items_.end()) return NULL;
  return *i;
}
