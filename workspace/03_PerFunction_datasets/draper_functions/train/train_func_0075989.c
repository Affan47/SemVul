get_letter(Token *token)
#else
get_letter(token)
	Token *token;
#endif
{
	token->tclass = tok_letter;
	token->tsubclass = src_text_buf[src_text_len++] = makeupper(curr_char);
	token->src_text = new_src_text(src_text_buf,src_text_len);

#ifdef DEBUG_FORLEX
    if(debug_lexer)
	(void)fprintf(list_fd,"\nLetter:\t\t\t%s",token->src_text);
#endif

	advance();

}
