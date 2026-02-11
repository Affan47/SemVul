SNSdbGetAttrDDS (ISNS_Attr **attr_indx, ISNS_Attr **key_indx, ISNS_Attr * src_attr,
                 ISNS_Msg_Descp * md, ISNS_Msg * p_rspmsg)
{
   int ii;
   int rval;
   int ddsKeyIndex;
   int ddKeyIndex;
   int iscsiKeyIndex;
   int ifcpKeyIndex;
   int ddsSymIndex;
   int found;
   ISNS_Key *key;
   ISNS_Attr *p_attr;
   SOIP_Dds *p_dds;

   rval = Check_Authorization (src_attr);
   if (rval != SUCCESS)
      return (ISNS_AUTH_FAILED_ERR);

   ISNSTouchEntity( src_attr );

   found = FALSE;

   ddsKeyIndex = -1;
   ddKeyIndex = -1;
   iscsiKeyIndex = -1;
   ifcpKeyIndex = -1;
   ddsSymIndex = -1;

   for (ii = 0; ii < MAX_PARSE_ATTRS && key_indx[ii]; ii++)
   {
      key = (ISNS_Key *)(key_indx[ii]);
      switch (key->tag)
      {
         case ISNS_ISCSI_NODE_ID:
            iscsiKeyIndex = ii;
            break;
         case ISNS_PORT_NAME:
            ifcpKeyIndex = ii;
            break;
         case ISNS_DD_ID:
            if (key->val.dd_id)
               ddKeyIndex = ii;
            break;
         case ISNS_DDS_ID:
            if (key->val.dds_id)
               ddsKeyIndex = ii;
            break;
         case ISNS_DDS_SYM_NAME:
            ddsSymIndex = ii;
            break;
         default:
            break;
      }
   }

   if (ddsKeyIndex != -1)
   {
      key = (ISNS_Key *)(key_indx[ddsKeyIndex]);
      rval = SNSdbGetAttrDDSEntry (*(uint32_t *) & key->val,
                  attr_indx, p_rspmsg);

      if (!rval)
         found = TRUE;
   }
   else if (ddKeyIndex != -1)
   {
      __DEBUG(isns_query_debug & 1, (Not implemented));
   }
   else if (ifcpKeyIndex != -1)
   {
      __DEBUG (isns_query_debug & 1, (Not implemented));
   }
   else if (iscsiKeyIndex != -1)
   {
      __DEBUG (isns_query_debug & 1, (Not implemented));
   }
   else
   {


      ISNS_DBKey key = { 0 };
      key.tag = DDS_ID_KEY;

      while (SNSdbGetNextOfKey (&key) == SUCCESS)
      {
         if (ddsSymIndex!=-1)
         {
            rval = read_DDSObject(key.val.dds_key.id, &p_dds, &entry);
            if (rval != SUCCESS)
                return rval;

            p_attr = (ISNS_Attr *)attr_indx[ddsSymIndex];

            if (strcmp(p_dds->sym_name, (char *)&p_attr->val))
               continue;
         }
         if (ERROR ==
             SNSdbGetAttrDDSEntry (key.val.dd_key.id, attr_indx, p_rspmsg))
            return (ERROR);
         found = TRUE;
      }
   }

   if (found != TRUE)
   {
      return (ISNS_NO_SUCH_ENTRY_ERR);
   }

   return (ISNS_NO_ERR);
}
