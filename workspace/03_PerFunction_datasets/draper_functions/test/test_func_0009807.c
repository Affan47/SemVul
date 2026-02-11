dump(unsigned Indent) const {
#ifndef NDEBUG
  raw_ostream &err = dbgs();
  err.indent(Indent);
  err << "DFSIn: " << DFSIn << " DFSOut: " << DFSOut << "\n";
  const MDNode *N = Desc;
  err.indent(Indent);
  N->dump();
  if (AbstractScope)
    err << std::string(Indent, ' ') << "Abstract Scope\n";

  if (!Children.empty())
    err << std::string(Indent + 2, ' ') << "Children ...\n";
  for (unsigned i = 0, e = Children.size(); i != e; ++i)
    if (Children[i] != this)
      Children[i]->dump(Indent + 2);
#endif
}
