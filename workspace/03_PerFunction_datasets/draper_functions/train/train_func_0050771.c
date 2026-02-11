get_reply (FILE *outfp)
{
  Reply *r;
  int done = 0;
  int retval = 0;


  if (fflush (serv_write) == EOF || ferror (serv_write))
    {
      fprintf (stderr, "%s: error writing to server\n", program_name);
    }

  while (! done)
    {
      r = server_reply ();

      if (r != NULL)
	{
	  if (r->type != REPLY_CONT)
	    {
	      done = 1;
	    }

	  if (debug)
	    {
	      fprintf (stderr, "%s: received %d `%s'\n",
		       program_name, r->state, r->text);
	    }

	  switch (r->state)
	    {
	    case CODE_GREETING:
	    case CODE_OK:
	    case CODE_SEND_PR:
	    case CODE_SEND_TEXT:
	    case CODE_SEND_CHANGE_REASON:
	    case CODE_INFORMATION_FILLER:
	      break;

	    case CODE_CLOSING:
	      if (debug)
		{
		  fprintf (stderr, "%s: server closing down\n", program_name);
		}
	      break;

	    case CODE_PR_READY:
	    case CODE_TEXT_READY:

	      if (prBeingRead != NULL)
		{
		  readPRFromServer (prBeingRead);
		}
	      else if (prList != NULL)
		{
		  readPRListFromServer ();
		}
	      else
		{
		  if (outfp != NULL)
		    read_server (outfp);
		  else
		    {
		      fprintf (stderr, "%s: unexpected %d received\n",
			       program_name, r->state);
		      safe_exit();
		    }
		}
	      break;

	    case CODE_INFORMATION:
	      if (outfp != NULL)
		fprintf (outfp, "%s\n", r->text);
	      break;

	    case CODE_NONEXISTENT_PR:
	    case CODE_UNREADABLE_PR:
	    case CODE_LOCKED_PR:
	    case CODE_FILE_ERROR:
	    case CODE_ERROR:
	    case CODE_NO_ADM_ENTRY:
	    case CODE_INVALID_FIELD_NAME:
	    case CODE_INVALID_PR_CONTENTS:
	    case CODE_INVALID_ENUM:
	    case CODE_INVALID_DATE:
	    case CODE_INVALID_EXPR:
	    case CODE_INVALID_DATABASE:
	    case CODE_INVALID_FIELD_EDIT:
	      fprintf (stderr, "%s: %s\n", program_name, r->text);
	      safe_exit ();
	      break;

	    case CODE_PR_NOT_LOCKED:
	      fprintf (stderr, "%s: PR is not locked\n", program_name);
	      safe_exit ();
	      break;

	    case CODE_GNATS_LOCKED:
	      fprintf (stderr, "%s: database is locked\n", program_name);
	      safe_exit ();
	      break;

	    case CODE_NO_PRS_MATCHED:
	      fprintf (stderr, "%s: no PRs matched\n", program_name);
	      safe_exit ();
	      break;

	    case CODE_NO_KERBEROS:
	      fprintf (stderr,
		       "%s: no Kerberos support, authentication failed\n",
		       program_name);

	    case CODE_NO_ACCESS:
#ifdef HAVE_KERBEROS
	      if (remember_krb_auth_ret)
		fprintf (stderr, "%s: error (%s) while attempting krb4-auth\n",
			 program_name,
			 krb_get_err_text (remember_krb_auth_ret));
	      else
		fprintf (stderr, "%s: access denied\n", program_name);
#else
	      fprintf (stderr, "%s: access denied\n", program_name);
#endif
	      safe_exit ();
	      break;

	    default:
	      fprintf (stderr, "%s: cannot understand %d `%s'\n",
		       program_name, r->state, r->text);
	      safe_exit ();
	      break;
	    }
	  retval = r->state;

	  free_reply (r);
	}
      else
	{
	  if (debug)
	    {
	      fprintf (stderr, "%s: null reply from the server\n",
		       program_name);
	    }
	  retval = 0;
	  done = 1;
	}
    }

  return retval;
}
