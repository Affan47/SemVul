do_stat ()

{
 uword i;
 char *thing;
 ulong cnum;

 if (arg_num<1 || arg_num>4)
   {
    wl_sj("S: The STATUS command requires zero to three arguments.");
    num_sev++;
    return;
   }


 if (arg_num == 1)
   {
    sprintf(linet1,"Last command: Severes=%lu, Errors=%lu, Warnings=%lu.",
            (ulong) old_sev, (ulong) old_err, (ulong) old_war);
    wl_sj(linet1);
    sprintf(linet1,"Totals      : Severes=%lu, Errors=%lu, Warnings=%lu.",
            (ulong) sum_sev, (ulong) sum_err, (ulong) sum_war);
    wl_sj(linet1);
    return;
   }


 for (i=1;i<arg_num;i++)
   {
    char ch=toupper(arg_arr[i][0]);
    unsigned num;
    if (ch!='W' && ch!='E' && ch!='S')
      {
       sprintf(linet1,
              "S: Argument %u of STATUS command has bad letter.",
               (unsigned) i);
       wl_sj(linet1);
       wl_sj("Arguments must be of the form ('W'|'E'|'S')<decimalnumber>.");
       num_sev++;
       return;
      }
    if (sscanf(&arg_arr[i][1],"%u",&num) != 1)
      {
       sprintf(linet1,
      "S: Argument %u of STATUS command has bad number.",
               (unsigned) i);
       wl_sj(linet1);
       wl_sj("   Arguments must be of the form ('W'|'E'|'S')<decimalnumber>.");
       num_sev++;
       return;
      }
    switch(ch)
      {
       case 'W': cnum=old_war; thing="warnings"; break;
       case 'E': cnum=old_err; thing="errors"  ; break;
       case 'S': cnum=old_sev; thing="severes" ; break;
       default : as_bomb("do_stat: case defaulted.");
      }
    if (cnum != num)
      {
       sprintf(linet1,
       "S: STATUS command detected wrong number of %s.",thing);
       wl_sj(linet1);
       sprintf(linet1, "Specifed %s=%u, Actual %s=%u.",
               thing,(unsigned) num,thing,(unsigned) cnum);
       wl_sj(linet1);
       num_sev++;
      }
   }
}
