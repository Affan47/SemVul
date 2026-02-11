ftio_write(struct ftio *ftio, void *data)
{
  int ret, n, nbytes;

  ret = -1;
  nbytes = 0;

  if (!(ftio->flags & FT_IO_FLAG_NO_SWAP)) {
#if BYTE_ORDER == BIG_ENDIAN
    if (ftio->fth.byte_order == FT_HEADER_LITTLE_ENDIAN)
      ftio->swapf((void*)data);
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
    if (ftio->fth.byte_order == FT_HEADER_BIG_ENDIAN)
      ftio->swapf((void*)data);
#endif
  }


  if (ftio->fth.flags & FT_HEADER_FLAG_COMPRESS) {

    ftio->zs.next_in = (Bytef*)data;
    ftio->zs.avail_in = ftio->rec_size;

    while (1) {

      if (deflate(&ftio->zs, Z_NO_FLUSH) != Z_OK) {
        fterr_warnx("deflate(): failed");
        goto ftio_write_out;
      }


      if (!ftio->zs.avail_out) {

        n = writen(ftio->fd, ftio->z_buf, FT_Z_BUFSIZE);

        if (n < 0) {
          fterr_warn("writen()");
          goto ftio_write_out;
        }

        if (n == 0) {
          fterr_warnx("writen(): EOF");
          goto ftio_write_out;
        }

        ftio->zs.next_out = (Bytef*)ftio->z_buf;
        ftio->zs.avail_out = FT_Z_BUFSIZE;

        nbytes += n;

        ret = 0;

      } else {

        ret = 0;
        break;

      }

    }


  } else {


    if ((ftio->d_start + ftio->rec_size) > ftio->d_end) {

      n = writen(ftio->fd, ftio->d_buf, ftio->d_start);

      if (n < 0) {
        fterr_warn("writen()");
        goto ftio_write_out;
      }

      if (n == 0) {
        fterr_warnx("writen(): EOF");
        goto ftio_write_out;
      }

      ftio->d_start = 0;

      nbytes += n;

    }

    bcopy(data, ftio->d_buf+ftio->d_start, ftio->rec_size);

    ftio->d_start += ftio->rec_size;

    ret = 0;

  }

ftio_write_out:

  if (!(ftio->flags & FT_IO_FLAG_NO_SWAP)) {
#if BYTE_ORDER == BIG_ENDIAN
    if (ftio->fth.byte_order == FT_HEADER_LITTLE_ENDIAN)
      ftio->swapf((void*)data);
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
    if (ftio->fth.byte_order == FT_HEADER_BIG_ENDIAN)
      ftio->swapf((void*)data);
#endif
  }

  if (ret < 0)
    return ret;
  else
    return nbytes;

}
