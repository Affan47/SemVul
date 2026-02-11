mcxIOtestOpen
(  mcxIO*         xf
,  mcxOnFail      ON_FAIL
)
   {  if (!xf->fp && mcxIOopen(xf, ON_FAIL) != STATUS_OK)
      {  mcxErr
         ("mcxIO", "cannot open file <%s> in mode %s", xf->fn->str, xf->mode)
      ;  return STATUS_FAIL
   ;  }
      return  STATUS_OK
;  }
