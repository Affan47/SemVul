free_edit_data (gftp_viewedit_data * ve_proc)
{
  int i;

  if (ve_proc->torequest)
    gftp_request_destroy (ve_proc->torequest, 1);
  if (ve_proc->filename)
    g_free (ve_proc->filename);
  if (ve_proc->remote_filename)
    g_free (ve_proc->remote_filename);
  for (i = 0; ve_proc->argv[i] != NULL; i++)
    g_free (ve_proc->argv[i]);
  g_free (ve_proc->argv);
  g_free (ve_proc);
}
