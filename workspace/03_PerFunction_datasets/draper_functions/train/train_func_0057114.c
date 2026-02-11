sort() {
  subEntries.sort(lessCat);
  for(std::list<AbstractEntry*>::iterator i = subEntries.begin(); i != subEntries.end(); i++) {
    (*i)->sort();
  }
}
