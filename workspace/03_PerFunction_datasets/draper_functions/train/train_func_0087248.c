close()
{

  png_write_end(priv->png_ptr, priv->info_ptr);
  if (setjmp(png_jmpbuf(priv->png_ptr))) {
    error(errInternal, -1, "Error during end of write");
    return false;
  }

  return true;
}
