parse_padding (CRTerm const	**value,
	       ccss_padding_t	 *padding)
{
	padding->base.state = ccss_property_parse_state (value);
	if (CCSS_PROPERTY_STATE_SET == padding->base.state &&
	    *value &&
	    TERM_NUMBER == (*value)->type) {

		padding->padding = (*value)->content.num->val;
		(*value) = (*value)->next;
		padding->base.state = CCSS_PROPERTY_STATE_SET;

		return true;
	}

	return false;
}
