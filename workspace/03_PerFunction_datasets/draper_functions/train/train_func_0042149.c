result_assignment(const string &result) const {
  stringstream out;
  if (!(_type->isVoid() || _type->isUndefined ()))  {
    if (_problem) {
      out << "::new (&result) ";
      out << result_type ("", true);
      out << " (";
    }
    else
      out << "result = ";
    if (_type->isAddress ())
      out << "&";
  }
  out << result;
  if (!(_type->isVoid() || _type->isUndefined ()))
    if (_problem)
      out << ")";
  return out.str ();
}
