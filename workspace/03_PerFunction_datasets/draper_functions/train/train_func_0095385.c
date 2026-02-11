match_antecessor_r (ccss_selector_t const	*self,
		    ccss_node_t			*node)
{
	ccss_node_t		*container;
	bool			 is_matching;

	container = ccss_node_get_container (node);
	if (container) {
		is_matching = ccss_selector_query (self, container);
		if (!is_matching) {
			is_matching = match_antecessor_r (self, container);
		}
		ccss_node_release (container);
	} else {
		is_matching = false;
	}

	return is_matching;
}
