perform_operation (char *dev, int desc, short op, int count)
{
  struct mtop control;

  control.mt_op = op;
  control.mt_count = count;
  if (rmtioctl (desc, MTIOCTOP, (char*)&control) == -1)
    error (MT_EXIT_FAILURE, errno, _("%s: rmtioctl failed"), dev);
}
