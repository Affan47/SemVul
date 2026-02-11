set_varbool(HSCATTR * attr, BOOL value)
{
   if (value)
      set_vartext(attr, attr->name);
   else
      set_vartext(attr, "");

   return (value);
}
