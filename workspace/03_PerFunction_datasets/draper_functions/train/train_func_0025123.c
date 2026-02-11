code_bitmap_directly(
  GBitmap &bm,const int dw, int dy,
  unsigned char *up2, unsigned char *up1, unsigned char *up0 )
{
      ZPCodec &zp=*gzp;

      while (dy >= 0)
        {
          int context=get_direct_context(up2, up1, up0, 0);
          for (int dx=0;dx < dw;)
            {
              int n = up0[dx++];
              zp.encoder(n, bitdist[context]);
              context=shift_direct_context(context, n, up2, up1, up0, dx);
            }

          dy -= 1;
          up2 = up1;
          up1 = up0;
          up0 = bm[dy];
        }
}
