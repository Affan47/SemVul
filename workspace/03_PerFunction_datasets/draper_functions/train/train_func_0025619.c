links_depth (struct file_link const *flink)
{
  int depth = 0;
  while (!IS_ROOT_FILE_LINK (flink))
    {
      depth++;
      flink = flink->fl_parent;
    }
  return depth;
}
