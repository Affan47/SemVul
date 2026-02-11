ISNSParseMsg (ISNS_Msg * msg, ISNS_Attr **attr_index, ISNS_Attr **key_index,
             ISNS_Attr **src_attr)
{
   int ii;
   int parse_status = SUCCESS;
   int num_attrs;
   int num_keys;


   if ((msg == NULL) || (attr_index == NULL))
      return (ERROR);

   for (ii = 0; ii < SNS_MAX_ATTRS; ii++)
      attr_index[ii] = NULL;

   for (ii = 0; ii < SNS_MAX_ATTRS; ii++)
      key_index[ii] = NULL;


   switch (msg->hdr.type)
   {
   case ISNS_HEART_BEAT:
         return (SUCCESS);
   case ISNS_REG_DEV_ATTR_REQ:
   case ISNS_ESI:
   case ISNS_SCN:
   case ISNS_DEV_GET_NXT_REQ:
   case ISNS_REG_DDS_REQ:
   case ISNS_REG_DD_REQ:
   case ISNS_DEREG_DDS_REQ:
   case ISNS_DEREG_DD_REQ:
   case ISNS_SCN_EVENT:
   case ISNS_DEREG_DEV_REQ:
   case ISNS_SCN_REG_REQ:
   case ISNS_SCN_DEREG_REQ:
   case ISNS_DEV_ATTR_QRY_REQ:
   case ISNS_DDS_GET_NXT_MEMBER_REQ:
   case ISNS_DD_GET_NXT_ISCSI_MEMBER_REQ:
   case ISNS_ENTITY_GET_NXT_PORTAL_REQ:

   case ISNS_REG_DEV_ATTR_RES:
   case ISNS_DEV_ATTR_QRY_RES:
   case ISNS_DEV_GET_NXT_RES:
   case ISNS_DEREG_DEV_RES:
   case ISNS_SCN_REG_RES:
   case ISNS_SCN_DEREG_RES:
   case ISNS_SCN_EVENT_RES:
   case ISNS_SCN_RES:
   case ISNS_REG_DD_RES:
   case ISNS_DEREG_DD_RES:
   case ISNS_REG_DDS_RES:
   case ISNS_DEREG_DDS_RES:
   case ISNS_ESI_RSP:
   case ISNS_DDS_GET_NXT_MEMBER_RES:
   case ISNS_DD_GET_NXT_ISCSI_MEMBER_RES:
   case ISNS_ENTITY_GET_NXT_PORTAL_RES:
      parse_status = ISNSProfileKeysAttr (msg, attr_index, &num_attrs,
                                          key_index, &num_keys, (ISNS_Attr **)src_attr);
      if(parse_status)
         __LOG_ERROR ("ISNSParseMSG error for msg->hdr.type=0x%x\n",msg->hdr.type);
      break;
   default:


      parse_status = ERROR;
      __LOG_ERROR ("ISNSParseMSG error for msg->hdr.type=0x%x unimplemented message type\n",msg->hdr.type);
      break;
   }

   return parse_status;
}
