get_hollerith(Token *token, int n)
#else
get_hollerith(token,n)
	Token *token;
	int n;
#endif
{
	int i;
	LINENO_t last_line_num;
	COLNO_t last_col_num;


	int strsize=n,
	    leadin=src_text_len+1,
	    fullsize=leadin+strsize+1;
	char *s;

	initial_flag = FALSE;

	s = new_src_text_alloc(fullsize);

	for(i=0; i<src_text_len; i++)
	  s[i] = src_text_buf[i];
	s[i++] = 'H';

	if(n==1)
	  inside_hollerith=FALSE;
	advance();

	last_col_num = col_num;
	last_line_num = line_num;

	for(i=0; i<n; i++) {
	  while(curr_char == EOL) {

	    COLNO_t col;
	    for(col=last_col_num; i<n && col<(COLNO_t)max_stmt_col; i++,col++) {
		s[leadin+i] = ' ';
	    }
	    last_col_num = col_num;
	    advance();
	  }
	  if(i==n) break;

	  if(curr_char == EOS || curr_char == EOF) {
	    COLNO_t col;
	    for(col=last_col_num; i<n && col<(COLNO_t)max_stmt_col; i++,col++) {
	      if(i < strsize)
		s[leadin+i] = ' ';
	    }
	    if(i < n) {
	      syntax_error((LINENO_t)last_line_num,(COLNO_t)last_col_num,
			   "Hollerith constant ends prematurely");
	      strsize=i;
	    }
	    break;
	  }
	  else {
	    s[leadin+i] = curr_char;
	    last_col_num = col_num;
	    last_line_num = line_num;
	    if(i==n-2)
	      inside_hollerith = FALSE;
	    advance();
	  }
	}

	if(strsize > 0)
	  s[leadin+strsize] = '\0';

	inside_hollerith = FALSE;
	token->tclass = tok_hollerith;
	token->value.string = s + leadin;
	token->size = n;
	token->src_text = s;
#ifdef DEBUG_FORLEX
	if(debug_lexer)
		(void)fprintf(list_fd,"\nHollerith:\t\t%s (from %s)",
			      token->value.string,
			      token->src_text);
#endif

}
