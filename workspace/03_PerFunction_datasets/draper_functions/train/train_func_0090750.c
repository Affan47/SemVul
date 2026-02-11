result_return() const {
  stringstream out;
  if (!(_type->isVoid () || _type->isUndefined ())) {
    out << "return ";
    if (_type->isAddress ())
      out << "*";
    out << "(";
    out << result_type ("&");
    out << ")result;" << endl;
  }
  return out.str ();
}
