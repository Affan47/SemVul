check_reqvar(HSCPRC * hp, HSCATTR * var)
{
   BOOL ok = TRUE;

   if ((var->varflag & VF_RECOMMENDED) && (!var->text))
      hsc_message(hp, MSG_MISS_RCMD_ATTR, "recommended %A missing", var);

   if ((var->varflag & VF_REQUIRED) && (!var->text))
   {
      hsc_message(hp, MSG_MISS_REQ_ATTR,
            "required %A missing", var);
      ok = FALSE;
   }

   return (ok);
}
