chmod_stub (XDR *xdr_in)
{
  int r;
  struct guestfs_chmod_args args;
  int mode;
  const char *path;

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_chmod_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  mode = args.mode;
  path = args.path;
  ABS_PATH (path, , goto done);

  NEED_ROOT (, goto done);
  r = do_chmod (mode, path);
  if (r == -1)

    goto done;

  reply (NULL, NULL);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_chmod_args, (char *) &args);
done_no_free:
  return;
}
