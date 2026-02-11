undo_history_redo_count (UNDO_HISTORY * history)
{
  if (history->length)
    return history->length - 1 - history->ix;

  return 0;
}
