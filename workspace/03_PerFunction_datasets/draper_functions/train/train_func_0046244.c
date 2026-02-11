action_result_assignment(const string &result) const {
  stringstream out;
  if (!(_type->isVoid() || _type->isUndefined ()))  {
    if (_problem) {
      out << "::new ((AC::ResultBuffer< ";
      out << result_type ("", false);
      out << " >*)__TJP::result ()) ";
      out << result_type ("", false);
      out << " (";
    }
    else {
      out << "*__TJP::result () = (" << result_type ("", false) << ")";
    }
    if (_type->isAddress ())
      out << "&";
  }
  out << result;
  if (!(_type->isVoid() || _type->isUndefined ()))
    if (_problem)
      out << ")";
  return out.str ();
}
