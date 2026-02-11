ifile_read_message (FILE * FP)
{
  ifile_lex * document;
  char token[MAX_STR_LEN];
  long int token_len;
  long int old_freq;
  htable * message = malloc(sizeof(htable));
  if (!message) abort();

  ifile_verbosify(ifile_verbose, "Reading message...\n");
  htable_init(message, 100, (unsigned long (*)(const void *, long int)) hash);

  DMZ2_start = clock();

  document = ifile_default_lexer->open_text_fp (ifile_default_lexer, FP);

  if (document)
    {
      token_len = ifile_default_lexer->get_word (ifile_default_lexer, document,
						 token, MAX_STR_LEN);
      while (token_len != 0)
	{
	  ifile_verbosify(ifile_debug, "Read \'%s\'.  length=%d\n", token,
			  token_len);

	  old_freq = (long int) htable_lookup(message, (void *) token);
	  htable_put(message, ((char *) token),
		     (void *) (old_freq+1));

	  token_len = ifile_default_lexer->get_word (ifile_default_lexer,
						     document, token, MAX_STR_LEN);
	}

      ifile_default_lexer->close (ifile_default_lexer, document);
    }
  else
    {
      ifile_verbosify(ifile_quiet, "Unable to read message.\n");
      ifile_free(message);
      return NULL;
    }

  ifile_verbosify(ifile_debug, "\n");
  DMZ_end = clock();
  ifile_verbosify(ifile_verbose,
		  "Finishing reading message.  Time used: %.3f sec\n",
		  ((float)(DMZ_end-DMZ2_start))/CLOCKS_PER_SECOND);

  return message;
}
