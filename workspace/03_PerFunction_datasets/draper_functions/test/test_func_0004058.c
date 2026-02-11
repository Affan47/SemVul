ccss_stylesheet_add_from_buffer	(ccss_stylesheet_t		*self,
				 char const			*buffer,
				 size_t				 size,
				 ccss_stylesheet_precedence_t	 precedence,
				 void				*user_data)
{
	enum CRStatus ret;

	g_return_val_if_fail (self, 0);
	g_return_val_if_fail (buffer, 0);
	g_return_val_if_fail (size, 0);

	self->current_descriptor++;
	ret = ccss_grammar_parse_buffer (self->grammar, buffer, size, precedence,
					 self->current_descriptor,
					 user_data,
					 self->groups, self->blocks);
	if (CR_OK == ret) {
		ccss_stylesheet_fix_dangling_selectors (self);
		return self->current_descriptor;
	} else {
		ccss_stylesheet_unload (self, self->current_descriptor);
		return 0;
	}
}
