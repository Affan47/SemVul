parse_command_line_pvs (void)
{
  char *out, *err;
  char *p, *pend;
  int r, i;
  guestfs_int_lvm_pv_list *ret;
  void *newp;

  ret = malloc (sizeof *ret);
  if (!ret) {
    reply_with_perror ("malloc");
    return NULL;
  }

  ret->guestfs_int_lvm_pv_list_len = 0;
  ret->guestfs_int_lvm_pv_list_val = NULL;

  r = command (&out, &err,
	       "lvm", "pvs",
	       "-o", lvm_pv_cols, "--unbuffered", "--noheadings",
	       "--nosuffix", "--separator", ",", "--units", "b", NULL);
  if (r == -1) {
    reply_with_error ("%s", err);
    free (out);
    free (err);
    free (ret);
    return NULL;
  }

  free (err);


  p = out;
  i = 0;
  while (p) {
    pend = strchr (p, '\n');
    if (pend) {
      *pend = '\0';
      pend++;
    }

    while (*p && c_isspace (*p))
      p++;

    if (!*p) {
      p = pend;
      continue;
    }


    newp = realloc (ret->guestfs_int_lvm_pv_list_val,
		    sizeof (guestfs_int_lvm_pv) * (i+1));
    if (newp == NULL) {
      reply_with_perror ("realloc");
      free (ret->guestfs_int_lvm_pv_list_val);
      free (ret);
      free (out);
      return NULL;
    }
    ret->guestfs_int_lvm_pv_list_val = newp;


    r = lvm_tokenize_pv (p, &ret->guestfs_int_lvm_pv_list_val[i]);
    if (r == -1) {
      reply_with_error ("failed to parse output of 'pvs' command");
      free (ret->guestfs_int_lvm_pv_list_val);
      free (ret);
      free (out);
      return NULL;
    }

    ++i;
    p = pend;
  }

  ret->guestfs_int_lvm_pv_list_len = i;

  free (out);
  return ret;
}
