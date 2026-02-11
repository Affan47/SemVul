DeRegisterEntity (void)
{
   char cmdLine[256];
   int c_size;
   int flag;
   ISNS_CMD cmd;

   printf ("DeRegistering Entity.\n");


   ISNSCreateHdr (ISNS_DEREG_DEV_REQ, &cmd, sizeof (cmd), 0);


   if (-1 == GetSrc (&cmd, 0))
      return;


   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);


   flag = FALSE;
   do
   {
      c_size = GetInput (cmdLine, "Entity ID", "(none)", sizeof (cmdLine));
      if (c_size != 0)
      {
         ISNSAppendAttr (&cmd, ISNS_ENTITY_ID, PAD4 (strlen (cmdLine)),
                         cmdLine, 0);
         flag = TRUE;
      }
   }
   while (c_size != 0);

   if (!flag)
   {
      printf ("***ERROR: At least one node is required.\n");
      return;
   }

   ISNSSendCmd (&cmd);
}
