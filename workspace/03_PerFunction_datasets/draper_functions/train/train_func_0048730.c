gt_scannedprjkey_add(GtScannedprjkeytable *scannedprjkeytable,
                          const char *keystring,
                          void *valueptr,
                          size_t sizeval,
                          bool readdouble,
                          bool *readflag)
{
  GtScannedprjkey rikvalue;

  rikvalue.keystring = keystring;
  rikvalue.readflag = readflag;
  rikvalue.readdouble = readdouble;
  if (readdouble)
  {
    gt_assert(sizeval == sizeof (double));
    rikvalue.uint32valueptr = NULL;
    rikvalue.uint64valueptr = NULL;
    rikvalue.doublevalueptr = valueptr;
    rikvalue.ptrdefined = true;
  } else
  {
    gt_assert(sizeval == 0 || sizeval == (size_t) 4 || sizeval == (size_t) 8);
    switch (sizeval)
    {
      case 0: rikvalue.uint32valueptr = NULL;
              rikvalue.uint64valueptr = NULL;
              rikvalue.ptrdefined = false;
              break;
      case 4: gt_assert(sizeof (uint32_t) == (size_t) 4);
              rikvalue.uint32valueptr = valueptr;
              rikvalue.uint64valueptr = NULL;
              rikvalue.ptrdefined = true;
              break;
      case 8: gt_assert(sizeof (uint64_t) == (size_t) 8);
              rikvalue.uint64valueptr = valueptr;
              rikvalue.uint32valueptr = NULL;
              rikvalue.ptrdefined = true;
              break;
    }
  }
  rikvalue.found = false;
  gt_array_add_elem(scannedprjkeytable->arr,&rikvalue,
                    sizeof (GtScannedprjkey));
}
