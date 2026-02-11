CanRead(const std::string& fn,
                               const std::vector<int8_t>& start) const
{
  if(!AbstrConverter::CanRead(fn, start)) {
    return false;
  }

  if((start[0] == '#' && start[1] == '\n') ||
     (start[0] == ' ' && start[1] == '\n' && start[2] == '\n')) {
    WARNING("Looks like an ascii file... not mine.");
    return false;
  }

  return true;
}
