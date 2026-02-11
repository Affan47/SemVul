EVAL_clear(EXPRESSION *expr, bool keep_error)
{
  ARRAY_delete(&expr->tree);

  ARRAY_delete(&expr->var);
  ARRAY_delete(&expr->unknown);
  ARRAY_delete(&expr->class);
  ARRAY_delete(&expr->cst);

  TABLE_delete(&expr->string);
  TABLE_delete(&expr->table);

  if (expr->pattern)
    FREE(&expr->pattern, "EVAL_clear");
  if (expr->code)
    FREE(&expr->code,"EVAL_clear");

	if (!keep_error)
		GB.FreeString(&expr->error);
}
