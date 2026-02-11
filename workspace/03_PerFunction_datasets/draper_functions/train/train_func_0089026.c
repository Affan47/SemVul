parse_fixup_v380_task_restr (sc_bool tasknotdone, sc_int task,
                             const sc_char *failmessage)
{

  if (task > 0)
    {
      sc_int var2;


      var2 = tasknotdone ? 1 : 0;
      parse_fixup_v380_restr (2, 2, task, var2, 0, failmessage);
    }
}
