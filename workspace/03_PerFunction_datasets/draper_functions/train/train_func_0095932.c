list_9p_stub (XDR *xdr_in)
{
  char **r;

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  r = do_list_9p ();
  if (r == NULL)

    goto done;

  struct guestfs_list_9p_ret ret;
  ret.mounttags.mounttags_len = count_strings (r);
  ret.mounttags.mounttags_val = r;
  reply ((xdrproc_t) &xdr_guestfs_list_9p_ret, (char *) &ret);
  free_strings (r);
done:
done_no_free:
  return;
}
