deregDDMember (char *ddid, char * iscsi_node)
{
   int dd_id;

   ISNSCreateHdr (ISNS_DEREG_DD_REQ, &cmd, sizeof (cmd), 0);
   ISNSAppendAttr (&cmd, ISNS_ISCSI_NODE_ID, PAD4 (strlen (CONTROL_NODE)),CONTROL_NODE, 0);

   dd_id = atoi (ddid);
   ISNSAppendAttr (&cmd, ISNS_DD_ID, 4, NULL, dd_id);

   ISNSAppendAttr (&cmd, 0, 0, NULL, 0);

   ISNSAppendAttr (&cmd, ISNS_DD_ISCSI_MEMBER, PAD4(strlen(iscsi_node)),
              iscsi_node, 0);

   ISNSSendCmd (&cmd);
}
