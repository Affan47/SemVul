run_task_is_loudly_restricted (sc_gameref_t game, sc_int task)
{
  sc_bool restrictions_passed;
  const sc_char *fail_message;


  if (!restr_eval_task_restrictions (game, task,
                                     &restrictions_passed, &fail_message))
    {
      sc_error ("run_task_is_loudly_restricted:"
                " restrictions error, %ld\n", task);
      return TRUE;
    }


  return !restrictions_passed && (fail_message != NULL);
}
