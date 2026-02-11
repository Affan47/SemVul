ldmtool_volume_hint_stub (XDR *xdr_in)
{
  char *r;
  struct guestfs_ldmtool_volume_hint_args args;
  const char *diskgroup;
  const char *volume;


  if (! optgroup_ldm_available ()) {
    reply_with_error_errno (ENOTSUP,
       "feature '%s' is not available in this\n"
       "build of libguestfs.  Read 'AVAILABILITY' in the guestfs(3) man page for\n"
       "how to check for the availability of features.",
       "ldm");
    goto done_no_free;
  }

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_ldmtool_volume_hint_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  diskgroup = args.diskgroup;
  volume = args.volume;

  r = do_ldmtool_volume_hint (diskgroup, volume);
  if (r == NULL)

    goto done;

  struct guestfs_ldmtool_volume_hint_ret ret;
  ret.hint = r;
  reply ((xdrproc_t) &xdr_guestfs_ldmtool_volume_hint_ret, (char *) &ret);
  free (r);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_ldmtool_volume_hint_args, (char *) &args);
done_no_free:
  return;
}
