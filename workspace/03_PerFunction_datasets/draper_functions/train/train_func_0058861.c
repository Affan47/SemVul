is_zero_device_stub (XDR *xdr_in)
{
  int r;
  struct guestfs_is_zero_device_args args;
  CLEANUP_FREE char *device = NULL;

  if (optargs_bitmask != 0) {
    reply_with_error ("header optargs_bitmask field must be passed as 0 for calls that don't take optional arguments");
    goto done_no_free;
  }

  memset (&args, 0, sizeof args);

  if (!xdr_guestfs_is_zero_device_args (xdr_in, &args)) {
    reply_with_error ("daemon failed to decode procedure arguments");
    goto done;
  }
  RESOLVE_DEVICE (args.device, device, , goto done);

  r = do_is_zero_device (device);
  if (r == -1)

    goto done;

  struct guestfs_is_zero_device_ret ret;
  ret.zeroflag = r;
  reply ((xdrproc_t) &xdr_guestfs_is_zero_device_ret, (char *) &ret);
done:
  xdr_free ((xdrproc_t) xdr_guestfs_is_zero_device_args, (char *) &args);
done_no_free:
  return;
}
