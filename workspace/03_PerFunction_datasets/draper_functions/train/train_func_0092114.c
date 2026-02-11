AllocatePartialMap(InstanceType instance_type,
                                 int instance_size) {
  Object* result = AllocateRawMap();
  if (result->IsFailure()) return result;


  reinterpret_cast<Map*>(result)->set_map(raw_unchecked_meta_map());
  reinterpret_cast<Map*>(result)->set_instance_type(instance_type);
  reinterpret_cast<Map*>(result)->set_instance_size(instance_size);
  reinterpret_cast<Map*>(result)->set_inobject_properties(0);
  reinterpret_cast<Map*>(result)->set_pre_allocated_property_fields(0);
  reinterpret_cast<Map*>(result)->set_unused_property_fields(0);
  reinterpret_cast<Map*>(result)->set_bit_field(0);
  reinterpret_cast<Map*>(result)->set_bit_field2(0);
  return result;
}
