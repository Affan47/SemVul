GetDDS (void)
{
   char buffer[MAX_PAYLOAD_SIZE];
   char cmdLine[256];
   int id;
   int key_type;

   printf ("Get DDS.\n");
   ISNSCreateHdr (ISNS_DEV_ATTR_QRY_REQ, &cmd, sizeof(cmd), 0);

   if (-1==GetSrc(&cmd, 0))
      return;


   key_type = 0;
   if (0 !=
       GetInput (cmdLine, "Key Type", "*0:none 1:DDS ID 2:DD ID 3:iSCSI Node",
                 sizeof (cmdLine)))
   {
      key_type = atoi (cmdLine);
   }
   switch (key_type)
   {
   case 1:
      if (0 != GetInput (cmdLine, "DDS ID", NULL, sizeof (cmdLine)))
      {
         id = atoi (cmdLine);
         ISNSAppendAttr (&cmd, ISNS_DDS_ID, 4, NULL, id);
      }
      break;
   case 2:
      if (0 != GetInput (cmdLine, "DD ID", NULL, sizeof (cmdLine)))
      {
         id = atoi (cmdLine);
         ISNSAppendAttr (&cmd, ISNS_DD_ID, 4, NULL, id);
      }
      break;
   case 3:
      if (0 != GetInput (cmdLine, "iSCSI Node ID", NULL, sizeof (cmdLine)))
      {
         id = atoi (cmdLine);
         ISNSAppendAttr (&cmd, ISNS_ISCSI_NODE_ID, PAD4 (strlen (cmdLine)),
                         cmdLine, 0);
      }
      break;

   default:
         ISNSAppendAttr (&cmd, ISNS_DDS_ID, 0, NULL, 0);
      break;
   }


   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);

   ISNSAppendAttr (&cmd, ISNS_DDS_ID, 0, NULL, 0);
   ISNSAppendAttr (&cmd, ISNS_DDS_SYM_NAME, 0, NULL, 0);
   ISNSAppendAttr (&cmd, ISNS_DDS_STATUS, 0, NULL, 0);
   ISNSAppendAttr (&cmd, ISNS_DD_ID, 0, NULL, 0);
   ISNSAppendAttr (&cmd, ISNS_DD_SYM_NAME, 0, NULL, 0);

   if (0 == ISNSSendCmd2 (&cmd, buffer, sizeof (buffer)))
      ParseDDSQuery (buffer);
}
