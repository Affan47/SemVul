mcx_tr_enc_dump
(  u32* enc
,  const char* tag
)
   {  int i = 0
   ;  fprintf(stdout, "(dumping %s\n", tag)
   ;  while (i<MAX_SPEC_INDEX+1)
      {  int meta = enc[i] >> 8
      ;  int val  = enc[i] & 0377
      ;  fprintf(stdout, "%6d%6d%6d\n", i, meta, val)
      ;  if (meta == C_EOF)
         break
      ;  i++
   ;  }
      fprintf(stdout, ")\n")
;  }
