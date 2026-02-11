_ecore_getopt_desc_is_sentinel(const Ecore_Getopt_Desc *desc)
{
   return (desc->shortname == '\0') && (!desc->longname);
}
