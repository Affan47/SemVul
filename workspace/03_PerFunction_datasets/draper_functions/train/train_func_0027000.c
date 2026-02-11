finish_objects (int method_type, int initp, tree body)
{
  tree fn;


  finish_compound_stmt (body);
  fn = finish_function (0);

  if (method_type == 'I')
    {
      DECL_STATIC_CONSTRUCTOR (fn) = 1;
      decl_init_priority_insert (fn, initp);
    }
  else
    {
      DECL_STATIC_DESTRUCTOR (fn) = 1;
      decl_fini_priority_insert (fn, initp);
    }

  expand_or_defer_fn (fn);
}
