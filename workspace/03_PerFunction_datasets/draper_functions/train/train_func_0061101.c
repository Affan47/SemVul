write_pair(int f,const std::string &name,const std::list<Exec>& value) {
  for(std::list<Exec>::const_iterator v = value.begin();
                 v != value.end(); ++v) {
    write_pair(f,name,*v);
  }
}
