pwrite_stub (XDR *xdr_in)
{
  int r;
  struct guestfs_pwrite_args args;
  const char *path;
  const char *content;
  size_t content_size;
  int64_t offset;

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_pwrite_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  path = args.path;
  ABS_PATH (path, , goto done);
  content = args.content.content_val;
  content_size = args.content.content_len;
  offset = args.offset;

  NEED_ROOT (, goto done);
  r = do_pwrite (path, content, content_size, offset);
  if (r == -1)

    goto done;

  struct guestfs_pwrite_ret ret;
  ret.nbytes = r;
  reply ((xdrproc_t) &xdr_guestfs_pwrite_ret, (char *) &ret);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_pwrite_args, (char *) &args);
done_no_free:
  return;
}
