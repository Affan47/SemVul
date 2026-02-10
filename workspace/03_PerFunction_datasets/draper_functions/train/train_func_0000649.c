ISNSAppendAttr (ISNS_Msg * msg, int tag, int size, char *p_value, int value)
{
   ISNS_Attr *attr;

   if (msg == NULL)
   {
      __LOG_ERROR ("Message is NULL");
      return (ERROR);
   }


   if (msg->hdr.msg_len == 0)
   {
      msg->hdr.msg_len = 4;
      msg->hdr.msg_len += ISNS_SIZEOF_TAG;
   }


   attr = (ISNS_Attr *)((char *) &msg->payload + msg->hdr.msg_len);


   attr->tag = tag;
   attr->len = size;

   if (p_value)
   {
      __ISNS_COPY (&attr->val, sizeof(attr->val), p_value, attr->len);
   }
   else if (attr->len == 8)
   {

      attr->val.timestamp.t_pad = 0;
      attr->val.timestamp.t_time = htonl (value);
   }
   else
   {
      *(uint32_t *) & attr->val = value;
   }

   msg->hdr.msg_len += attr->len + ISNS_SIZEOF_TAG;
   attr = (ISNS_Attr *)((char *) attr + attr->len + ISNS_SIZEOF_TAG);

   return (ISNS_NO_ERR);
}
