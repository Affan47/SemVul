c_enable_warnings (bool enable)
{
  if (enable)
    {
      --c_inhibit_evaluation_warnings;
      fold_undefer_and_ignore_overflow_warnings ();
    }
}
