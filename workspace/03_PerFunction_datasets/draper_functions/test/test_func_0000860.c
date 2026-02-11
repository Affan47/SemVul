internal_lxattrlist_stub (XDR *xdr_in)
{
  guestfs_int_xattr_list *r;
  struct guestfs_internal_lxattrlist_args args;
  const char *path;
  char **names;


  if (! optgroup_linuxxattrs_available ()) {
    reply_with_error_errno (ENOTSUP,
       "feature '%s' is not available in this\n"
       "build of libguestfs.  Read 'AVAILABILITY' in the guestfs(3) man page for\n"
       "how to check for the availability of features.",
       "linuxxattrs");
    goto done_no_free;
  }

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_internal_lxattrlist_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  path = args.path;
  ABS_PATH (path, , goto done);

  names = realloc (args.names.names_val,
                sizeof (char *) * (args.names.names_len+1));
  if (names == NULL) {
    reply_with_perror ("realloc");
    goto done;
  }
  names[args.names.names_len] = NULL;
  args.names.names_val = names;

  NEED_ROOT (, goto done);
  r = do_internal_lxattrlist (path, names);
  if (r == NULL)

    goto done;

  struct guestfs_internal_lxattrlist_ret ret;
  ret.xattrs = *r;
  free (r);
  reply ((xdrproc_t) xdr_guestfs_internal_lxattrlist_ret, (char *) &ret);
  xdr_free ((xdrproc_t) xdr_guestfs_internal_lxattrlist_ret, (char *) &ret);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_internal_lxattrlist_args, (char *) &args);
done_no_free:
  return;
}
