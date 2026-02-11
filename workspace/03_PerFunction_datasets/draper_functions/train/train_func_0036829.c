UpdateDD (void)
{
   char cmdLine[256];
   int id;

   printf ("Updating DD.\n");
   ISNSCreateHdr (ISNS_REG_DD_REQ, &cmd, sizeof (cmd), 0);

   if (-1==GetSrc(&cmd, 0))
      return;

   if (GetInput (cmdLine, "DD ID", NULL, sizeof (cmdLine)))
   {
      id = atoi (cmdLine);
      ISNSAppendAttr (&cmd, ISNS_DD_ID, 4, NULL, id);
   }
   else
   {
      printf ("***ERROR: Required.\n");
   }


   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);


   if (GetInput (cmdLine, "DD Sym Name", NULL, sizeof (cmdLine)))
   {
      ISNSAppendAttr (&cmd, ISNS_DD_SYM_NAME, PAD4 (strlen (cmdLine)),
                      cmdLine, 0);
   }

   ISNSSendCmd (&cmd);
}
