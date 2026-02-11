getName() {
  std::stringstream name;

  if(getBlock() != NULL) {
    if(getBlock()->hasName()) {
      std::string tempName(getBlock()->getName());
      name << tempName.c_str() << " (" << _uid << ")";
    } else
      name << "<unnamed> (" << _uid << ")";
  } else
    name << "<null> (" << _uid << ")";

  return name.str();
}
