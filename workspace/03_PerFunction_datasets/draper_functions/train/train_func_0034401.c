DeRegisterISCSI (void)
{
   char cmdLine[256];


   ISNSCreateHdr (ISNS_DEREG_DEV_REQ, &cmd, sizeof (cmd), 0);


   if (-1 == GetSrc (&cmd, 0))
      return;


   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);


   if (0 == GetInput (cmdLine, "KEY: iSCSI Node Id", NULL, sizeof (cmdLine)))
   {
      printf ("***ERROR: required.\n");
      return;
   }

   ISNSAppendAttr (&cmd, ISNS_ISCSI_NODE_ID, PAD4 (strlen (cmdLine)), cmdLine, 0);


   ISNSSendCmd (&cmd);
}
