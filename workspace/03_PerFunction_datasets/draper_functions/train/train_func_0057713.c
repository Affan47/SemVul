md_detail_stub (XDR *xdr_in)
{
  char **r;
  struct guestfs_md_detail_args args;
  CLEANUP_FREE char *md = NULL;


  if (! optgroup_mdadm_available ()) {
    reply_with_error_errno (ENOTSUP,
       "feature '%s' is not available in this\n"
       "build of libguestfs.  Read 'AVAILABILITY' in the guestfs(3) man page for\n"
       "how to check for the availability of features.",
       "mdadm");
    goto done_no_free;
  }

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_md_detail_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  RESOLVE_DEVICE (args.md, md, , goto done);

  r = do_md_detail (md);
  if (r == NULL)

    goto done;

  struct guestfs_md_detail_ret ret;
  ret.info.info_len = count_strings (r);
  ret.info.info_val = r;
  reply ((xdrproc_t) &xdr_guestfs_md_detail_ret, (char *) &ret);
  free_strings (r);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_md_detail_args, (char *) &args);
done_no_free:
  return;
}
