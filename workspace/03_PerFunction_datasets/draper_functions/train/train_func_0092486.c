linclude_eval (CSPARSE *parse, CSTREE *node, CSTREE **next)
{
  NEOERR *err = STATUS_OK;
  CSARG val;

  err = eval_expr(parse, &(node->arg1), &val);
  if (err) return nerr_pass(err);
  if (val.op_type & (CS_TYPE_NUM | CS_TYPE_VAR_NUM))
  {
    char buf[256];
    long int n_val;

    n_val = arg_eval_num (parse, &val);
    snprintf (buf, sizeof(buf), "%ld", n_val);
    err = parse->output_cb (parse->output_ctx, buf);
  }
  else
  {
    char *s = arg_eval (parse, &val);

    if (s)
    {
      CSPARSE *cs = NULL;
      do {
	err = cs_init_internal(&cs, parse->hdf, parse);
	if (err) break;
	err = cs_parse_file(cs, s);
	if (!(node->flags & CSF_REQUIRED))
	{
	  nerr_handle(&err, NERR_NOT_FOUND);
	}
	if (err) break;
	err = cs_render(cs, parse->output_ctx, parse->output_cb);
	if (err) break;
      } while (0);
      cs_destroy(&cs);
    }
  }
  if (val.alloc) free(val.s);

  *next = node->next;
  return nerr_pass(err);
}
