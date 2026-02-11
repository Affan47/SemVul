_gl_completion_action(GetLine *gl, void *data, CplMatchFn *match_fn,
				 int list_only, const char *name,
				 const char *keyseq)
{
  KtKeyFn *current_fn;
  void *current_data;


  KtKeyFn *action_fn = list_only ? gl_list_completions : gl_complete_word;


  if(_kt_lookup_action(gl->bindings, name, &current_fn, &current_data) == 0) {


    if(current_fn == action_fn) {
      GlCplCallback *cb = (GlCplCallback *) current_data;
      cb->fn = match_fn;
      cb->data = data;
    } else {
      errno = EINVAL;
      _err_record_msg(gl->err,
        "Illegal attempt to change the type of an existing completion action",
        END_ERR_MSG);
      return 1;
    };


  } else {


    GlCplCallback *cb = (GlCplCallback *) _new_FreeListNode(gl->cpl_mem);
    if(!cb) {
      errno = ENOMEM;
      _err_record_msg(gl->err, "Insufficient memory to add completion action",
		      END_ERR_MSG);
      return 1;
    };


    cb->fn = match_fn;
    cb->data = data;


    if(_kt_set_action(gl->bindings, name, action_fn, cb)) {
      _err_record_msg(gl->err, _kt_last_error(gl->bindings), END_ERR_MSG);
      _del_FreeListNode(gl->cpl_mem, (void *) cb);
      return 1;
    };
  };


  if(keyseq && _kt_set_keybinding(gl->bindings, KTB_NORM, keyseq, name)) {
    _err_record_msg(gl->err, _kt_last_error(gl->bindings), END_ERR_MSG);
    return 1;
  };
  return 0;
}
