fiasco_decoder_get_width (fiasco_decoder_t *decoder)
{
   dfiasco_t *dfiasco = cast_dfiasco (decoder);

   if (!dfiasco)
      return 0;
   else
   {
      unsigned width;

      if (dfiasco->enlarge_factor >= 0)
	 width = dfiasco->wfa->wfainfo->width << dfiasco->enlarge_factor;
      else
	 width = dfiasco->wfa->wfainfo->width >> - dfiasco->enlarge_factor;

      return width & 1 ? width + 1 : width;
   }
}
