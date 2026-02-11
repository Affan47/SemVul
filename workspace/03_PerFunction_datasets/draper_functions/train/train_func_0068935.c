flow_skip (struct linereader *ldfile, const struct charmap_t *charmap,
	   struct locale_collate_t *collate)
{
  int level = 0;
  struct token *now;
  enum token_t nowtok;
  while (1)
    {
      lr_ignore_rest (ldfile, 0);
      now = lr_token (ldfile, charmap, NULL, NULL, 0);
      nowtok = now->tok;
      if (nowtok == tok_eof)
	break;
      else if (nowtok == tok_ifdef || nowtok == tok_ifndef)
	++level ;
      else if (nowtok == tok_else)
	{
	  if (strcmp (collate->flow_control->name, "else") == 0)
	    lr_error (ldfile,
		      _("%s: `else' statement at `%s:%Zu' cannot be followed by another `else' statement"),
		      "LC_COLLATE", collate->flow_control->name, collate->flow_control->line);
	  if (level == 0)
	    {
	      collate->flow_control->name = "else";
	      collate->flow_control->file = ldfile->fname;
	      collate->flow_control->line = ldfile->lineno;
	      break;
	    }
	}
      else if (nowtok == tok_endif)
	{
	  if (level == 0)
	    {
	      collate->flow_control = collate->flow_control->last;
	      break;
	    }
	  --level ;
	}
    }
  if (nowtok == tok_eof)
    WITH_CUR_LOCALE (error (0, 0, _("\
%s: unterminated `%s' flow control beginning at %s:%Zu"),
				 "LC_COLLATE", collate->flow_control->name,
				 collate->flow_control->file,
				 collate->flow_control->line));
  return now;
}
