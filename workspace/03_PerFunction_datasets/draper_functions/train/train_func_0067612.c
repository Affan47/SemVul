checkBounds
(  unsigned char type
,  void*       var
,  int         (*lftRlt) (const void*, const void*)
,  void*       lftBound
,  int         (*rgtRlt) (const void*, const void*)
,  void*       rgtBound
)
   {  int lftOk, rgtOk
   ;  if (checkBoundsUsage(type, var, lftRlt, lftBound, rgtRlt, rgtBound))
      {  mcxErr("checkBounds PBD", "internal error -- cannot validate")
      ;  return STATUS_CB_PBD
   ;  }
      lftOk =   !lftRlt || lftRlt(var, lftBound)
   ;  rgtOk =   !rgtRlt || rgtRlt(var, rgtBound)
   ;  return (lftOk && rgtOk) ? STATUS_OK : STATUS_FAIL
;  }
