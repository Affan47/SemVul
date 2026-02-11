set_parameter(int param, CHAIN_OPERATOR::parameter_t value)
{
  if (param == 1) {
    deltafixes_rep.resize(static_cast<int>(value));
  }
  else if (param > 1 && param - 2 < static_cast<int>(deltafixes_rep.size())) {
    deltafixes_rep[param - 2] = value;
  }
}
