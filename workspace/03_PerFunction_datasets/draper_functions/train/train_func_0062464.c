operator<<(OutputCharStream &os, long n)
{
  if (n < 0)
    return os << '-' << (unsigned long)-n;
  else
    return os << (unsigned long)n;
}
