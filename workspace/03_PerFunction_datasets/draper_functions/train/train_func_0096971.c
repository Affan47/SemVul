logmask_to_str(const log_mask_t *mask, char *buf, int size)
{
   int  last_sev = -1;
   bool is_range = false;
   int  sev;
   int  len = 0;

   if ((mask == NULL) || (buf == NULL) || (size <= 0))
   {
      if ((buf != NULL) && (size > 0))
      {
         *buf = 0;
      }
      return(buf);
   }

   for (sev = 0; sev < 256; sev++)
   {
      if (logmask_test(mask, sev))
      {
         if (last_sev == -1)
         {
            len += snprintf(&buf[len], size - len, "%d,", sev);
         }
         else
         {
            is_range = true;
         }
         last_sev = sev;
      }
      else
      {
         if (is_range)
         {
            buf[len - 1] = '-';
            len         += snprintf(&buf[len], size - len, "%d,", last_sev);
            is_range     = false;
         }
         last_sev = -1;
      }
   }


   if (is_range && (last_sev != -1))
   {
      buf[len - 1] = '-';
      len         += snprintf(&buf[len], size - len, "%d", last_sev);
   }
   else
   {

      if (len > 0)
      {
         len--;
      }
   }

   buf[len] = 0;

   return(buf);
}
