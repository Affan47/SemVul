ParseNamedEnum(const EnumDescriptor* descriptor,
                    const string& name,
                    int* value) {
  const EnumValueDescriptor* d = descriptor->FindValueByName(name);
  if (d == NULL) return false;
  *value = d->number();
  return true;
}
