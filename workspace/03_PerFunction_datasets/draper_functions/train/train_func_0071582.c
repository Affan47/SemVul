chunky_copy_pixels(Microtek2_Scanner *ms, uint8_t *from)
{
    Microtek2_Device *md;
    uint32_t pixel;
    int color;

    DBG(30, "chunky_copy_pixels: from=%p, pixels=%d, fp=%p, depth=%d\n",
             from, ms->ppl, (void *) ms->fp, ms->depth);

    md = ms->dev;
    if ( ms->depth > 8 )
      {
        if ( !( md->model_flags & MD_16BIT_TRANSFER ) )
          {
            int scale1;
            int scale2;
            uint16_t val16;

            scale1 = 16 - ms->depth;
            scale2 = 2 * ms->depth - 16;
            for ( pixel = 0; pixel < ms->ppl; pixel++ )
              {
                for ( color = 0; color < 3; color++ )
                  {
                    val16 = *( (uint16_t *) from + 3 * pixel + color );
                    val16 = ( val16 << scale1 ) | ( val16 >> scale2 );
                    fwrite((void *) &val16, 2, 1, ms->fp);
                  }
              }
          }
        else
          {
            fwrite((void *) from, 2, 3 * ms->ppl, ms->fp);
          }
      }
    else if ( ms->depth == 8 )
      {
        fwrite((void *) from, 1, 3 * ms->ppl, ms->fp);
      }
    else
      {
        DBG(1, "chunky_copy_pixels: Unknown depth %d\n", ms->depth);
        return SANE_STATUS_IO_ERROR;
      }

    return SANE_STATUS_GOOD;
}
