cuddZddSymmSiftingBackward(
  DdManager * table,
  Move * moves,
  int  size)
{
    int		i;
    int		i_best;
    Move	*move;
    int		res;

    i_best = -1;
    for (move = moves, i = 0; move != NULL; move = move->next, i++) {
	if (move->size < size) {
	    i_best = i;
	    size = move->size;
	}
    }

    for (move = moves, i = 0; move != NULL; move = move->next, i++) {
	if (i == i_best) break;
	if ((table->subtableZ[move->x].next == move->x) &&
	    (table->subtableZ[move->y].next == move->y)) {
	    res = cuddZddSwapInPlace(table, move->x, move->y);
	    if (!res) return(0);
	}
	else {
	    res = zdd_group_move_backward(table, move->x, move->y);
	}
	if (i_best == -1 && res == size)
	    break;
    }

    return(1);

}
