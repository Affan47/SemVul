value_lexer_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		lexer_unref (value->data[0].v_pointer);
	}
}
