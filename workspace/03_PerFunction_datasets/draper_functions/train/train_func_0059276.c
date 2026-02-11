get_pred_parent(struct filter_pred *pred, struct filter_pred *preds,
		int index, enum move_type *move)
{
	if (pred->parent & FILTER_PRED_IS_RIGHT)
		*move = MOVE_UP_FROM_RIGHT;
	else
		*move = MOVE_UP_FROM_LEFT;
	pred = &preds[pred->parent & ~FILTER_PRED_IS_RIGHT];

	return pred;
}
