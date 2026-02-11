rem_msg_dest(MSGS *msg, int dest_code, int msg_type, char *where)
{
   DEST *d;

   for (d=msg->dest_chain; d; d=d->next) {
      Dmsg2(850, "Remove_msg_dest d=%p where=%s\n", d, NPRT(d->where));
      if (bit_is_set(msg_type, d->msg_types) && (dest_code == d->dest_code) &&
          ((where == NULL && d->where == NULL) ||
                     (strcmp(where, d->where) == 0))) {
         Dmsg3(850, "Found for remove d=%p msgtype=%d destcode=%d\n",
               d, msg_type, dest_code);
         clear_bit(msg_type, d->msg_types);
         Dmsg0(850, "Return rem_msg_dest\n");
         return;
      }
   }
}
