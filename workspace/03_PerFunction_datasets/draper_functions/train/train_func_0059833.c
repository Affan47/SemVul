mcxTRtranslate
(  char*    src
,  mcxTR*   tr
)
   {  dim i,j
   ;  int prev =  INT_MAX
   ;  dim len  =  strlen(src)
   ;  u32* tbl =  tr->tlt

   ;  for (i=0,j=0;i<len;i++)
      {  u8  idx     = *(src+i)
      ;  u32 tok     =  tbl[idx]
      ;  u8 idxmap   =  tok & 0377
      ;  u8 val      =  0

      ;  val = (tok >> 8) & MCX_TR_TRANSLATE ? idxmap : idx

      ;  if ((tbl[val] >> 8) & MCX_TR_DELETE)
         continue

      ;  if (!((tbl[val] >> 8) & MCX_TR_SQUASH) || val != prev)
         {  *(src+j++) =  (char) val
         ;  prev = val
      ;  }
      }
      *(src+j) = '\0'
   ;  return (ofs) j
;  }
