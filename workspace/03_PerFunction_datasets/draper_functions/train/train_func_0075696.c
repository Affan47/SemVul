get_ip_data(struct marvell_session *ps, SANE_Byte *data, SANE_Int maxLength, SANE_Int *length)
{
   int ip_ret=IP_INPUT_ERROR;
   unsigned int outputAvail=maxLength, outputUsed=0, outputThisPos;
   unsigned char *input, *output = data;
   unsigned int inputAvail, inputUsed=0, inputNextPos;

   if (!ps->ip_handle)
   {
      BUG("invalid ipconvert state\n");
      goto bugout;
   }

   if (ps->bb_get_image_data(ps, outputAvail))
      goto bugout;

   if (ps->cnt > 0)
   {
      inputAvail = ps->cnt;
      input = ps->buf;
   }
   else
   {
      input = NULL;
      inputAvail = 0;
   }


   ip_ret = ipConvert(ps->ip_handle, inputAvail, input, &inputUsed, &inputNextPos, outputAvail, output, &outputUsed, &outputThisPos);

   DBG6("input=%p inputAvail=%d inputUsed=%d inputNextPos=%d output=%p outputAvail=%d outputUsed=%d outputThisPos=%d ret=%x\n", input,
         inputAvail, inputUsed, inputNextPos, output, outputAvail, outputUsed, outputThisPos, ip_ret);

   if (data)
      *length = outputUsed;


   if (ip_ret & IP_DONE && outputUsed)
      ip_ret &= ~IP_DONE;

bugout:
   return ip_ret;
}
