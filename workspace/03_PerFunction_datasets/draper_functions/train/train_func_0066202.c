pull(int source)
{
  if (suppressed(source)) {
    return 0;
  } else {
    return input(source).pull();
  }
}
