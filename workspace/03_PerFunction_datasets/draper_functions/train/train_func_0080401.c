process_requests (struct ProcessingContext *pc)
{
  while (1)
    {
      unsigned char code;

      if (1 != EXTRACTOR_read_all_ (pc->in, &code, 1))
	{
	  LOG ("Failed to read next request\n");
	  break;
	}
      switch (code)
	{
	case MESSAGE_INIT_STATE:
	  if (0 != handle_init_message (pc))
	    {
	      LOG ("Failure to handle INIT\n");
	      return;
	    }
	  break;
	case MESSAGE_EXTRACT_START:
	  if (0 != handle_start_message (pc))
	    {
	      LOG ("Failure to handle START\n");
	      return;
	    }
	  break;
	case MESSAGE_UPDATED_SHM:
	  LOG ("Illegal message\n");

	  return;
	case MESSAGE_DISCARD_STATE:

	  continue;
	default:
	  LOG ("Received invalid messag %d\n", (int) code);

	  return;
	}
    }
}
