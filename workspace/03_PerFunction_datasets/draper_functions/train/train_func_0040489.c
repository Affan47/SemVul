property_factory (ccss_grammar_t const	*grammar,
		  ccss_block_t		*block,
		  char const		*name,
		  CRTerm const		*values,
		  void			*user_data)
{
	ccss_property_generic_t	*property, p;

	memset (&p, 0, sizeof (p));

	p.base.vtable = peek_property_class ();
	p.base.state = ccss_property_parse_state (&values);
	p.name = g_strdup (name);
	if (p.base.state == CCSS_PROPERTY_STATE_SET) {
		p.values = (CRTerm *) values;
		cr_term_ref (p.values);
	}

	property = g_new0 (ccss_property_generic_t, 1);
	*property = p;
	ccss_block_add_property (block, name, &property->base);

	return true;
}
