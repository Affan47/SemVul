_glcpp_parser_expand_token_list (glcpp_parser_t *parser,
				 token_list_t *list)
{
	token_node_t *node_prev;
	token_node_t *node, *last = NULL;
	token_list_t *expansion;
	active_list_t *active_initial = parser->active;

	if (list == NULL)
		return;

	_token_list_trim_trailing_space (list);

	node_prev = NULL;
	node = list->head;

	while (node) {

		while (parser->active && parser->active->marker == node)
			_parser_active_list_pop (parser);

		expansion = _glcpp_parser_expand_node (parser, node, &last);
		if (expansion) {
			token_node_t *n;

			for (n = node; n != last->next; n = n->next)
				while (parser->active &&
				       parser->active->marker == n)
				{
					_parser_active_list_pop (parser);
				}

			_parser_active_list_push (parser,
						  node->token->value.str,
						  last->next);


			if (expansion->head) {
				if (node_prev)
					node_prev->next = expansion->head;
				else
					list->head = expansion->head;
				expansion->tail->next = last->next;
				if (last == list->tail)
					list->tail = expansion->tail;
			} else {
				if (node_prev)
					node_prev->next = last->next;
				else
					list->head = last->next;
				if (last == list->tail)
					list->tail = NULL;
			}
		} else {
			node_prev = node;
		}
		node = node_prev ? node_prev->next : list->head;
	}


	while (parser->active && parser->active != active_initial)
		_parser_active_list_pop (parser);

	list->non_space_tail = list->tail;
}
