update_exit_button()
{

  if (gc_board_get_current() &&
      gc_board_get_current()->previous_board == NULL)
    {

      current_flags |= GC_BAR_EXIT;
      current_flags &= ~GC_BAR_HOME;
    }
  else
    {
      current_flags &= ~GC_BAR_EXIT;
      current_flags |= GC_BAR_HOME;
    }
}
