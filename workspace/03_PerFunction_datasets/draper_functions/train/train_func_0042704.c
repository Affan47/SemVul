end(seq_no seq)
{
  if (seq > last)
    {
      return "invalid sequence number";
    }
  else if (pActive[seq])
    {
      pActive[seq] = 0;
      pCommand[seq] = 0;
      decide_disposition();
#ifdef DEBUG_COMMANDS
	  fprintf(stderr,
		  "^A%c %u: inserting=%c\n",
		  'E',
		  (unsigned) seq,
		  inserting ? 'Y' : 'N');
#endif
	  return NULL;
    }
  else
    {
      return "unmatched ^AE";
    }
}
