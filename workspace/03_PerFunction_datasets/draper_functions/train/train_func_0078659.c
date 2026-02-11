maybe_unlink (const char *file)
{
  if (debug)
    {
      notice ("[Leaving %s]\n", file);
      return;
    }

  if (file == output_file && !may_unlink_output_file)
    return;

  unlink_if_ordinary (file);
}
