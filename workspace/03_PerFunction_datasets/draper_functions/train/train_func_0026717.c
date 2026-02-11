send_chunk (const guestfs_chunk *chunk)
{
  char buf[GUESTFS_MAX_CHUNK_SIZE + 48];
  char lenbuf[4];
  XDR xdr;
  uint32_t len;

  xdrmem_create (&xdr, buf, sizeof buf, XDR_ENCODE);
  if (!xdr_guestfs_chunk (&xdr, (guestfs_chunk *) chunk)) {
    fprintf (stderr, "guestfsd: send_chunk: failed to encode chunk\n");
    xdr_destroy (&xdr);
    return -1;
  }

  len = xdr_getpos (&xdr);
  xdr_destroy (&xdr);

  xdrmem_create (&xdr, lenbuf, 4, XDR_ENCODE);
  xdr_u_int (&xdr, &len);
  xdr_destroy (&xdr);

  int err = (xwrite (sock, lenbuf, 4) == 0
             && xwrite (sock, buf, len) == 0 ? 0 : -1);
  if (err) {
    fprintf (stderr, "guestfsd: send_chunk: write failed\n");
    exit (EXIT_FAILURE);
  }

  return err;
}
