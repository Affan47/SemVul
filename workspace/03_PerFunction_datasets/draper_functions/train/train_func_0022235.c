RegCustom3 (void)
{
   char buffer[256];
   memset (buffer, 0, sizeof (buffer));


   ISNSCreateHdr (ISNS_REG_DEV_ATTR_REQ, &cmd, sizeof (cmd), 0);


   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);
   memcpy (buffer, "Entity 1", sizeof (buffer));
   ISNSAppendAttr (&cmd, ISNS_ENTITY_ID, PAD4 (strlen (buffer)), buffer, 0);
   ISNSAppendAttr (&cmd, ISNS_ENTITY_TYPE, 4, NULL, 2);


   memset (buffer, 0, sizeof (buffer));
   strcpy (buffer, "PORTNAM1");
   ISNSAppendAttr (&cmd, ISNS_PORT_NAME, 8, buffer, 0);
   ISNSAppendAttr (&cmd, ISNS_PORT_ID, 4, "PID1", 1);
   ISNSAppendAttr (&cmd, ISNS_PORT_TYPE, 4, NULL, 0xFF12);
   ISNSAppendAttr (&cmd, ISNS_FABRIC_PORT_NAME, 8, "FP_NAME1", 0);
   ISNSAppendAttr (&cmd, ISNS_FC_HARD_ADDR, 4, "HRD1", 0);
   {
      char tempip[16];
      memset (tempip, 0, sizeof (tempip));
      *(uint32_t *) & tempip[12] = inet_addr (DEFAULT_IP_ADDR);
      ISNSAppendAttr (&cmd, ISNS_FC_PORT_IP, 16, tempip, 0);
   }
   ISNSAppendAttr (&cmd, ISNS_FC_COS, 4, "COS 1", 0);

   ISNSAppendAttr (&cmd, ISNS_IFCP_SCN_BITMAP, 4, NULL, 0x1f);

   ISNSSendCmd (&cmd);
   WaitForKey ();
   return;
}
