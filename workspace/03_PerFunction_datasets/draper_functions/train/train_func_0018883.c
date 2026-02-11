start_io(void)
{
  if (triggered_rep != true) {
    if (io_mode() == io_read)
      fork_input_process();
    else
      fork_output_process();

    triggered_rep = true;
  }
}
