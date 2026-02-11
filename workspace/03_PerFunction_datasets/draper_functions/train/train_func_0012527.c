hivex_node_get_value_stub (XDR *xdr_in)
{
  int64_t r;
  struct guestfs_hivex_node_get_value_args args;
  int64_t nodeh;
  const char *key;


  if (! optgroup_hivex_available ()) {
    reply_with_error_errno (ENOTSUP,
       "feature '%s' is not available in this\n"
       "build of libguestfs.  Read 'AVAILABILITY' in the guestfs(3) man page for\n"
       "how to check for the availability of features.",
       "hivex");
    goto done_no_free;
  }

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_hivex_node_get_value_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  nodeh = args.nodeh;
  key = args.key;

  r = do_hivex_node_get_value (nodeh, key);
  if (r == -1)

    goto done;

  struct guestfs_hivex_node_get_value_ret ret;
  ret.valueh = r;
  reply ((xdrproc_t) &xdr_guestfs_hivex_node_get_value_ret, (char *) &ret);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_hivex_node_get_value_args, (char *) &args);
done_no_free:
  return;
}
