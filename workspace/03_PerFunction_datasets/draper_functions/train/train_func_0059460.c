read_line()
    {
      int read_ret = linebuf.read_line(in);

      if (echo_diff_output)
        {

          if (0 == read_ret)
            {
              printf("%s", linebuf.c_str());
            }
        }
      return read_ret;
    }
