AaffWriteSegmentArg (t_pAaff pAaff, const char *pName, unsigned int Argument)
{
   CHK (AaffWriteSegment (pAaff, pName, Argument, NULL, 0))
   return NO_ERROR;
}
