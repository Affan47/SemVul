print (ostream &out, const char *inner, bool prefix) const {
  ostringstream declarator;
  declarator << "&";
  if (inner)
    declarator << inner;
  if (base ())
    base ()->print (out, declarator.str ().c_str (), true);
  else
    out << "<any> " << declarator.str ();
}
