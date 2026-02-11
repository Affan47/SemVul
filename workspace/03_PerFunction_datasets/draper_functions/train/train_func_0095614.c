mime_var_destroy (mime_var_t * obj)
{
  int status;
  struct sigaction new_action;

  if (obj->name)
    {
      free (obj->name);
      obj->name = NULL;
    }
  if (obj->filename)
    {
      free (obj->filename);
      obj->filename = NULL;
    }
  if (obj->type)
    {
      free (obj->type);
      obj->type = NULL;
    }
  if (obj->tempname)
    {
      free (obj->tempname);
      obj->tempname = NULL;
    }
  buffer_destroy (&(obj->value));
  if (obj->fh)
    {
      close (abs (obj->fh));
      if (global.uploadhandler)
	{
	  wait (&status);
	  new_action.sa_handler = SIG_DFL;
	  sigemptyset (&new_action.sa_mask);
	  new_action.sa_flags = 0;
	  sigaction (SIGPIPE, &new_action, NULL);
	}
      obj->fh = 0;
    }
}
