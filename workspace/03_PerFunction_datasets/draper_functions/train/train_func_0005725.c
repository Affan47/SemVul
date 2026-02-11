type_finder(const void *_key, const void *_ti)
{
	const struct token *token = _key;
	const struct type *const *ti = _ti;
	const struct type *type = *ti;

	if (token->size != type->name->size)
		return token->size - type->name->size;
	else
		return memcmp(token->content, type->name->content,
			      token->size);
}
