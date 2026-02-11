validate_property(char *rnam, int32 proptyp)
{
 if (__to_vpipnam(__wrks1, proptyp) == NULL || proptyp == vpiUndefined)
  {
   __vpi_err(1819, vpiError,
    "%s: property %d illegal or out of range", rnam, proptyp);
   return(FALSE);
  }
 return(TRUE);
}
