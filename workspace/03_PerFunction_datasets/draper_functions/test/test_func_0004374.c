infer_outside_loop(Topform c)
{


  Topform copy = copy_inference(c);
  cl_process_simplify(copy);
  if (copy->justification->next == NULL) {

    delete_clause(copy);
    cl_process(c);
  }
  else {
    assign_clause_id(c);
    copy->justification->u.id = c->id;
    clist_append(c, Glob.disabled);
    cl_process(copy);
  }

  limbo_process(FALSE);
}
