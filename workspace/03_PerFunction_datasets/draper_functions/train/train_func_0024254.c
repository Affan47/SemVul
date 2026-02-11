getSDNodeNamed(const std::string &Name) const {
  Record *N = Records.getDef(Name);
  if (!N || !N->isSubClassOf("SDNode")) {
    errs() << "Error getting SDNode '" << Name << "'!\n";
    exit(1);
  }
  return N;
}
