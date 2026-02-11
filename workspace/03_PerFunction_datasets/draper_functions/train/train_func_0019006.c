_gnutls_comp_deinit (comp_hd_t handle, int d)
{
  if (handle != NULL)
    {
      switch (handle->algo)
        {
#ifdef HAVE_LIBZ
        case GNUTLS_COMP_DEFLATE:
          {
            if (d)
              inflateEnd (handle->handle);
            else
              deflateEnd (handle->handle);
            break;
          }
#endif
        default:
          break;
        }
      gnutls_free (handle->handle);
      gnutls_free (handle);

    }
}
