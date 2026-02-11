lexer_insert_token (Lexer* self, LexerTokenType type) {
	LexerToken* result = NULL;
	LexerToken* token = NULL;
	LexerToken* _tmp0_ = NULL;
	PreLexer* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	PreLexer* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	PreLexer* _tmp5_ = NULL;
	gint _tmp6_ = 0;
	LexerTokenType _tmp7_ = 0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = lexer_token_new ();
	token = _tmp0_;
	_tmp1_ = self->priv->prelexer;
	_tmp2_ = pre_lexer_get_marked_substring (_tmp1_);
	_g_free0 (token->text);
	token->text = _tmp2_;
	_tmp3_ = self->priv->prelexer;
	_tmp4_ = _tmp3_->mark_index;
	token->start_index = (guint) _tmp4_;
	_tmp5_ = self->priv->prelexer;
	_tmp6_ = _tmp5_->index;
	token->end_index = (guint) _tmp6_;
	_tmp7_ = type;
	token->type = _tmp7_;
	result = token;
	return result;
}
