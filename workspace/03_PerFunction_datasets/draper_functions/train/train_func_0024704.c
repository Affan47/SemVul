str() {
  stringstream ss;

  ss << lvalue->str() << " = " << rvalue->str();

  return ss.str();
}
