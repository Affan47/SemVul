valeur_latex()const{
  std::ostringstream so;
  so << val;
  std::string s(so.str());
  std::string::size_type epos=s.find('e',0);
  if (epos!=std::string::npos){
    s.erase(epos,1);
    s.insert(epos,"\\times 10^{");
    s=s+"}";
  }
  return (std::string) s;
}
