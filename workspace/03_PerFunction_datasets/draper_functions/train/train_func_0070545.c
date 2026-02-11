GRSThtcpNOPresponseMake(char **message, int *message_length,
                            unsigned int trans_id)


{
   *message_length =
        asprintf(message,
                       "%c%c"
                       "%c%c"
                       "%c%c"
                       "%c%c"
                       "%c%c%c%c"
                       "%c%c",
            0, 0,
            0, 0,
            0, 0,
            GRSThtcpNOPop * 16, 1,
            0, 0, 0, 0,
            0, 2);

   if (*message_length < 0) return GRST_RET_FAILED;

   (*message)[0] = *message_length / 256;
   (*message)[1] = *message_length % 256;

   (*message)[4] = (*message_length - 6) / 256;
   (*message)[5] = (*message_length - 6) % 256;

   memcpy(&((*message)[8]), &trans_id, 4);

   return GRST_RET_OK;
}
