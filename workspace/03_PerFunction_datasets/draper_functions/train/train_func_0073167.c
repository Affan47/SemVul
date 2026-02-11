addMembre(const Membre * m){
  for(int i=0; i<m->size(); i++){
    addMol((*m)[i]);
  }
}
