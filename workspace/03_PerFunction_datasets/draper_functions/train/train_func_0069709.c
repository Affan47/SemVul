journal_next_stub (XDR *xdr_in)
{
  int r;


  if (! optgroup_journal_available ()) {
    reply_with_error_errno (ENOTSUP,
       "feature '%s' is not available in this\n"
       "build of libguestfs.  Read 'AVAILABILITY' in the guestfs(3) man page for\n"
       "how to check for the availability of features.",
       "journal");
    goto done_no_free;
  }

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  r = do_journal_next ();
  if (r == -1)

    goto done;

  struct guestfs_journal_next_ret ret;
  ret.more = r;
  reply ((xdrproc_t) &xdr_guestfs_journal_next_ret, (char *) &ret);
done:
done_no_free:
  return;
}
