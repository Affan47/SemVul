ompi_mpi_errors_are_fatal_win_handler(struct ompi_win_t **win,
					   int *error_code, ...)
{
  char *name;
  struct ompi_communicator_t *abort_comm = NULL;
  va_list arglist;

  va_start(arglist, error_code);

  if (NULL != win) {
      name = (*win)->w_name;
  } else {
      name = NULL;
  }
  backend_fatal("win", abort_comm, name, error_code, arglist);
  va_end(arglist);
}
