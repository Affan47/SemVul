make_arg_names(Token *tlist, ArgListHeader *alhead, ArgListHeader *prev_alhead)
#else
make_arg_names(tlist, alhead, prev_alhead)
     Token *tlist;
     ArgListHeader *alhead, *prev_alhead;
#endif
{
	int h, i, n, prev_n;
	Token *s;
#ifdef KEEP_ARG_NAMES
	char *name;
	char expr_text[MAXEXPRTEXT+2];
#else
	static char expr[]="expr",
	            var[]="var";
#endif
	ArgListElement *arglist, *prev_arglist;

	n = alhead->numargs;
	if(n > 0) {
	  arglist = alhead->arg_array;
	  if(prev_alhead != NULL) {
	    prev_n = prev_alhead->numargs;
	    prev_arglist = prev_alhead->arg_array;
	  }
	  for(i=0, s=tlist; i<n; i++, s=s->next_token) {


	    if(is_true(ID_EXPR,s->TOK_flags)
		    && !is_true(ARRAY_ELEMENT_EXPR,s->TOK_flags)) {
#ifdef KEEP_ARG_NAMES
	      h = s->value.integer;
	      name = hashtab[h].loc_symtab->name;
#else
	      name = var;
#endif
	    }
	    else {
#ifdef KEEP_ARG_NAMES
	      int ncopied;
	      ncopied = cp_tree_src_text(expr_text,
			(s->left_token == NULL?
				s:
				s->left_token),
			MAXEXPRTEXT+1);
	      if(ncopied > MAXEXPRTEXT)

		(void)strcpy(expr_text+MAXEXPRTEXT-2,"..");
	      name = expr_text;
#else
	      arglist[i].name = expr;
#endif
	    }
#ifdef KEEP_ARG_NAMES

	    if(prev_alhead != NULL && i < prev_n
		 && strcmp(name,prev_arglist[i].name) == 0) {
	      name = prev_arglist[i].name;
	    }
	    else if(is_true(ID_EXPR,s->TOK_flags)
		    && !is_true(ARRAY_ELEMENT_EXPR,s->TOK_flags)) {
	      if(hashtab[h].glob_symtab != NULL) {
		name = hashtab[h].glob_symtab->name;
	      }
	      else if(hashtab[h].com_glob_symtab != NULL) {
		name = hashtab[h].com_glob_symtab->name;
	      }
	      else
		name = new_global_string(name);
	    }
	    else
	      name = new_global_string(name);
#endif
	    arglist[i].name = name;
	  }
	}
}
