cmd_version(void)
{
   if (!(flags & XBOARD))
     printf ("%s %s\n", PROGRAM, VERSION);
   else
     printf ("Chess\n");
}
