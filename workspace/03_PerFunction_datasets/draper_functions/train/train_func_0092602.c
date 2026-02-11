tnPushToken
(  telRaam* raam
)
   {  i32  toktype = raam->toktype
   ;  tn* new = tnNewToken(raam->token->str, toktype, 0.0, 0)

   ;  if (!new)
      return STATUS_FAIL

   ;  if (toktype == TOKEN_CONST)
         new->fval   =  raam->fval
      ,  new->ival   =  raam->ival
      ,  new->flags  =  raam->flags

   ;  else if
      (  toktype == TOKEN_BINOP
      || toktype == TOKEN_UNIOP
      )
      {  opHook* oh = raam->toktype == TOKEN_BINOP ? opHookDir+3 : opHookDir+0


      ;  while (oh->opname)
         {  if (!strcmp(oh->opname, raam->token->str))
            {  new->optype = oh->optype
            ;  new->opid   = oh->opid
            ;  break
         ;  }
            oh++
      ;  }
         if (!oh->opname)
         {  mcxErr("tnPushToken", "no such operator: <%s>", raam->token->str)
         ;  tnFree(new, NULL)
         ;  return STATUS_FAIL
      ;  }
      }
      else if (raam->toktype == TOKEN_FUN)
      {
   ;  }
      tnLink3(raam->node, new, NULL)
   ;  raam->node = new
   ;  return STATUS_OK
;  }
