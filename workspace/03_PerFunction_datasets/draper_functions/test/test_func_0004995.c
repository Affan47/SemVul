cleanup_slaves (void)
{
  for (;;)
    {

      size_t n = slaves_count;
      if (n == 0)
        break;
      n--;
      slaves_count = n;

      if (slaves[n].used)
        {
          pid_t slave = slaves[n].child;


          kill (slave, TERMINATOR);
        }
    }
}
