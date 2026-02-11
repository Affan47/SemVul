get_packet_prot (decode_proto_t *dp)
{
  guint i;

  g_assert(lkentry && lkentry->fun);
  lkentry->fun(dp);


  for (i = STACK_SIZE ; i>0 ; --i)
    {
      if (dp->pr->protonames[i])
        {
          dp->pr->protonames[0] = g_strdup(dp->pr->protonames[i]);
          break;
        }
    }
}
