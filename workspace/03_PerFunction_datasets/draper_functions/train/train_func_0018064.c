unparse_declarations(StringAccum &sa, const String &indent) const
{

  Vector<String> conf;
  for (int i = 0; i < nelements(); i++) {
    sa << indent << _element_names[i] << " :: " << _elements[i]->class_name();
    String conf = (initialized() ? _elements[i]->configuration() : _element_configurations[i]);
    if (conf.length())
      sa << "(" << conf << ")";
    sa << ";\n";
  }

  if (nelements() > 0)
    sa << "\n";
}
