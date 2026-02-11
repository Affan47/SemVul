AddMsg (void *p_msg, int size)
{
   int i;
   if (FALSE == msgInitFlag)
   {
      for (i = 0; i < MSG_Q_SIZE; i++)
      {
         msg_q[i].p_msg = NULL;
      }

      msgCurrentIndex = 0;
      msgCurrentHead = 0;
      msgInitFlag = TRUE;
   }
   msg_q[msgCurrentIndex].p_msg = (void *)malloc (size);
   msg_q[msgCurrentIndex].size = size;
   memcpy (msg_q[msgCurrentIndex].p_msg, p_msg, size);

   msgCurrentIndex = (msgCurrentIndex + 1) % MSG_Q_SIZE;

   return (0);
}
