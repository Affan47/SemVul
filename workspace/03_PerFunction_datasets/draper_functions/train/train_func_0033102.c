RequiredRegisterKind(int virtual_register) const {
  if (virtual_register < first_artificial_register_) {
    HValue* value = graph_->LookupValue(virtual_register);
    if (value != NULL && value->representation().IsDouble()) {
      return DOUBLE_REGISTERS;
    }
  } else if (double_artificial_registers_.Contains(
      virtual_register - first_artificial_register_)) {
    return DOUBLE_REGISTERS;
  }

  return GENERAL_REGISTERS;
}
