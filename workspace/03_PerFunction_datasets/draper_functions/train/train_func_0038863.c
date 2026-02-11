send_message_file(struct Client *source_p, MessageFile *motdToPrint)
{
  MessageFileLine *linePointer;
  MotdType motdType;
  const char *from, *to;

  if (motdToPrint == NULL)
    return(-1);

  motdType = motdToPrint->motdType;

  from = ID_or_name(&me, source_p->from);
  to = ID_or_name(source_p, source_p->from);

  switch (motdType)
  {
    case USER_MOTD:
      if (motdToPrint->contentsOfFile == NULL)
        sendto_one(source_p, form_str(ERR_NOMOTD), from, to);
      else
      {
	sendto_one(source_p, form_str(RPL_MOTDSTART),
		   from, to, me.name);

	for (linePointer = motdToPrint->contentsOfFile; linePointer;
	     linePointer = linePointer->next)
	{
	  sendto_one(source_p, form_str(RPL_MOTD),
		     from, to, linePointer->line);
	}

	sendto_one(source_p, form_str(RPL_ENDOFMOTD), from, to);
      }
      break;

    case USER_LINKS:
      if (motdToPrint->contentsOfFile != NULL)
      {
	for (linePointer = motdToPrint->contentsOfFile; linePointer;
	     linePointer = linePointer->next)
	{
	  sendto_one(source_p, ":%s 364 %s %s",
		     from, to, linePointer->line);
	}
      }
      break;

    case OPER_MOTD:
      if (motdToPrint->contentsOfFile != NULL)
      {
	sendto_one(source_p, form_str(RPL_OMOTDSTART),
		   me.name, source_p->name, me.name);

	sendto_one(source_p, form_str(RPL_OMOTD),
		   me.name, source_p->name, motdToPrint->lastChangedDate);

	for (linePointer = motdToPrint->contentsOfFile; linePointer;
	     linePointer = linePointer->next)
	{
	  sendto_one(source_p, form_str(RPL_OMOTD),
		     me.name, source_p->name, linePointer->line);
	}
	sendto_one(source_p, form_str(RPL_ENDOFOMOTD),
		   me.name, source_p->name);
      }
      break;

  case ISSUPPORT:
      if (motdToPrint->contentsOfFile != NULL)
      {
	for (linePointer = motdToPrint->contentsOfFile; linePointer;
	     linePointer = linePointer->next)
	{
	  sendto_one(source_p, form_str(RPL_ISUPPORT),
		     me.name, source_p->name, linePointer->line);
	}
      }
    break;

    default:
      break;
  }

  return(0);
}
