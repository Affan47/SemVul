SendESIRsp (void)
{
   char cmdLine[256];
   ISNS_CMD cmd;

   memset (cmdLine, 0, sizeof (cmdLine));

   printf ("Sending ESI Response.\n");
   ISNSCreateHdr (ISNS_REG_DEV_ATTR_REQ, &cmd, sizeof (cmd), 0);


   if (0 == GetInput(cmdLine, "Entity ID", NULL, sizeof(cmdLine)))
   {
      printf ("***ERROR: Cmd Line required.\n");
      exit (-1);
   }

   ISNSAppendAttr (&cmd, ISNS_ENTITY_ID, PAD4 (strlen (cmdLine)), cmdLine, 0);

   ISNSJustSendCmd (&cmd);
}
