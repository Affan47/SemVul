sanei_w_call (Wire * w,
	      SANE_Word procnum,
	      WireCodecFunc w_arg, void *arg,
	      WireCodecFunc w_reply, void *reply)
{

  DBG (3, "sanei_w_call: wire %d (old status %d)\n", w->io.fd, w->status);
  w->status = 0;
  sanei_w_set_dir (w, WIRE_ENCODE);

  DBG (4, "sanei_w_call: sending request (procedure number: %d)\n", procnum);
  sanei_w_word (w, &procnum);
  (*w_arg) (w, arg);

  if (w->status == 0)
    {
      DBG (4, "sanei_w_call: receiving reply\n");
      sanei_w_set_dir (w, WIRE_DECODE);
      (*w_reply) (w, reply);
    }

  if (w->status != 0)
    DBG (2, "sanei_w_call: error status %d\n", w->status);
  DBG (4, "sanei_w_call: done\n");
}
