rnode_iterator_next(struct rnode_iterator *iter)
{


	if (is_leaf(iter->current)) {
		if (iter->current == iter->root) {


			struct rnode dummy;
			if (NULL == iter->current->current_child) {
				iter->current->current_child = &dummy;
					SHOW;
				return iter->current;
			} else {
				iter->current->current_child = NULL;
				SHOW_END;
				return NULL;
			}
		} else {


			iter->current = iter->current->parent;
			SHOW;
			return iter->current;
		}
	}


	if (iter->current->current_child
	    == iter->current->last_child) {
		iter->current->current_child = NULL;
		if (iter->root == iter->current) {
			SHOW_END;
			return NULL;
		} else {
			iter->current = iter->current->parent;
			SHOW;
			return iter->current;
		}
	}


	if (NULL == iter->current->current_child)

		iter->current->current_child = iter->current->first_child;
	else
		iter->current->current_child =
			iter->current->current_child->next_sibling;

	iter->current = iter->current->current_child;
	SHOW;
	return iter->current;
}
