val_int()
{
  DBUG_ASSERT(fixed == 1);
  String tmp;
  String *swkb= args[0]->val_str(&tmp);
  Geometry_buffer buffer;

  null_value= args[0]->null_value ||
              !(Geometry::construct(&buffer, swkb->ptr(), swkb->length()));

  return 0;
}
