get_gc_function (object obj)
{
  if (BOOLEEQ (obj, O(object_boole_clr)))   return GXclear;
  if (BOOLEEQ (obj, O(object_boole_and)))   return GXand;
  if (BOOLEEQ (obj, O(object_boole_andc2))) return GXandReverse;
  if (BOOLEEQ (obj, O(object_boole_1)))     return GXcopy;
  if (BOOLEEQ (obj, O(object_boole_andc1))) return GXandInverted;
  if (BOOLEEQ (obj, O(object_boole_2)))     return GXnoop;
  if (BOOLEEQ (obj, O(object_boole_xor)))   return GXxor;
  if (BOOLEEQ (obj, O(object_boole_ior)))   return GXor;
  if (BOOLEEQ (obj, O(object_boole_nor)))   return GXnor;
  if (BOOLEEQ (obj, O(object_boole_eqv)))   return GXequiv;
  if (BOOLEEQ (obj, O(object_boole_c2)))    return GXinvert;
  if (BOOLEEQ (obj, O(object_boole_orc2)))  return GXorReverse;
  if (BOOLEEQ (obj, O(object_boole_c1)))    return GXcopyInverted;
  if (BOOLEEQ (obj, O(object_boole_orc1)))  return GXorInverted;
  if (BOOLEEQ (obj, O(object_boole_nand)))  return GXnand;
  if (BOOLEEQ (obj, O(object_boole_set)))   return GXset;

  my_type_error(O(object_xlib__gc_function),obj);


}
