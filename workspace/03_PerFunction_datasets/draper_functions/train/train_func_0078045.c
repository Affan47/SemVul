BuildLoadKeyedGeneric(HValue* object,
                                                   HValue* key) {
  HValue* context = environment()->LookupContext();
  return new(zone()) HLoadKeyedGeneric(context, object, key);
}
