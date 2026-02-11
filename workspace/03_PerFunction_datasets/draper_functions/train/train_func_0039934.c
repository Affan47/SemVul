isEmpty() const
{
  return (title().isEmpty() &&
          artist().isEmpty() &&
          album().isEmpty() &&
          comment().isEmpty() &&
          genre().isEmpty() &&
          year() == 0 &&
          track() == 0);
}
