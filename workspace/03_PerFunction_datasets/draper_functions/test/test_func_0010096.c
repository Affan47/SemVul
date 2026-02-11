xtypeIsFloat(int xtype)
{
  int isFloat = FALSE;
  if ( xtype == NC_FLOAT || xtype == NC_DOUBLE ) isFloat = TRUE;
  return isFloat;
}
