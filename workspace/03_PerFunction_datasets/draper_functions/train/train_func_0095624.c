composeMailMessage (PR *pr, PR *oldPR, const char *formatName,
		    FormatNamedParameter *parameters,
		    BadFields bad_fields,
		    ErrorDesc *err ATTRIBUTE_UNUSED)
{
  MailMessageFormat format = findMailFormat (pr->database, formatName);
  FILE *msg;
  char *fromAddr;
  char *toAddr = NULL;
  char *replyToAddr = NULL;
  MailAddressList *p;

  if (format == NULL)
    {
      return -1;
    }

  block_signals ();

  fromAddr = generateMailAddress (pr, oldPR, format->fromAddress, parameters);
  if (fromAddr == NULL)
    {
      fromAddr = (char *)gnatsAdminMailAddr (pr->database);
    }
  for (p = format->toAddresses; p != NULL; p = p->next)
    {
      char *theAddr = generateMailAddress (pr, oldPR, p->address, parameters);
      if (theAddr != NULL)
	{
	  toAddr = insertAddress (toAddr, theAddr);
	  free (theAddr);
	}
    }

  for (p = format->replyTo; p != NULL; p = p->next)
    {
      char *theAddr = generateMailAddress (pr, oldPR, p->address, parameters);
      if (theAddr != NULL)
	{
	  replyToAddr = insertAddress (replyToAddr, theAddr);
	  free (theAddr);
	}
    }

  msg = open_mail_file (pr->database);
  if (msg == NULL)
    {
      return -1;
    }
  fprintf (msg, "From: %s\n", fromAddr);
  fprintf (msg, "To: %s\n", toAddr);
  if (replyToAddr != NULL)
    {
      fprintf (msg, "Reply-To: %s\n", replyToAddr);
    }
  process_format (msg, NULL, pr, oldPR, format->header, "\n", parameters);
  fprintf (msg, "\n");


  if (bad_fields != NULL)
    {

      BadFields t;
      for (t = bad_fields; t != NULL ; t = nextBadField (t))
	{
	  FieldIndex field = badFieldIndex (t);
	  const char *value = badFieldValue (t);
	  if (value != NULL)
	    {
	      fprintf (msg,
		       "\tNote: There was a bad value `%s' for the field `%s'.\n\tIt was set to the default value of `%s'.\n\n",
		       value, fieldDefForIndex (field)->name,
		       fieldDefForIndex (field)->default_value);
	    }
	  else
	    {
	      fprintf (msg,
		       "\tNote: There was a missing value for the field `%s'.\n\tIt was set to the default value of `%s'.\n\n",
		       fieldDefForIndex (field)->name,
		       fieldDefForIndex (field)->default_value);
	    }
	}
    }

  process_format (msg, NULL, pr, oldPR, format->body, "\n", parameters);
  close_mail_file (msg);

  free (fromAddr);
  free (toAddr);
  if (replyToAddr != NULL)
    {
      free (replyToAddr);
    }

  unblock_signals ();

  return 0;
}
