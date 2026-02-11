operator<<(std::ostream& output, const libtest::Timer& arg)
{
  struct timespec temp;
  arg.difference(temp);

  if (temp.tv_sec > 60)
  {
    output << temp.tv_sec / 60;
    output << "." << temp.tv_sec % 60;
  }
  else
  {
    output << temp.tv_sec;
  }

  output << ":";
  output << std::setfill('0') << std::setw(9) << temp.tv_nsec;

  return output;
}
