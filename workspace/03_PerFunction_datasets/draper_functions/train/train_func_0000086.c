unlink2 (PARAM_UNUSED void * dummy, const char * filename)
{
  message (msg_tool | msg_file, (stderr, "Unlinking file `%s'\n", filename));


  unlink (filename);
}
