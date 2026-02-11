dbg_cnt_process_opt (const char *arg)
{
   const char *start = arg;
   const char *next;
   do {
     next = dbg_cnt_process_single_pair (arg);
     if (next == NULL)
       break;
   } while (*next == ',' && (arg = next + 1));

   if (next == NULL || *next != 0)
     {
       char *buffer = XALLOCAVEC (char, arg - start + 2);
       sprintf (buffer, "%*c", (int)(1 + (arg - start)), '^');
       error ("cannot find a valid counter:value pair:");
       error ("-fdbg-cnt=%s", start);
       error ("          %s", buffer);
     }
}
