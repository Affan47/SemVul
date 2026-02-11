terrain_belongs_to_class(const struct terrain *pterrain,
                              enum terrain_class class)
{
  switch(class) {
   case TC_LAND:
     return !is_ocean(pterrain);
   case TC_OCEAN:
     return is_ocean(pterrain);
  }

  fc_assert(FALSE);
  return FALSE;
}
