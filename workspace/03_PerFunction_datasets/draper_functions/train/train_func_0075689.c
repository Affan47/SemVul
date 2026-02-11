mcxIOnewName
(  mcxIO*         xf
,  const char*    newname
)
   {  if (!mcxTingEmpty(xf->fn, 0))
      return STATUS_FAIL

   ;  return mcxIOappendName(xf, newname)
;  }
