_read_workload(int fd, Bytes& workload)
{
  while (1)
  {
    char buffer[1024];

    ssize_t read_ret= read(fd, buffer, sizeof(buffer));

    if (read_ret == -1)
    {
      error::perror("read");
    }
    else if (read_ret == 0)
    {
      break;
    }

    workload.reserve(workload.size() + static_cast<size_t>(read_ret));
    for (size_t x= 0; x < static_cast<size_t>(read_ret); x++)
    {
      workload.push_back(buffer[x]);
    }
  }
}
