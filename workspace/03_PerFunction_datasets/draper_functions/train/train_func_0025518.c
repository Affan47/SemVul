fiasco_decoder_new (const char *filename, const fiasco_d_options_t *options)
{
   try
   {
      bitfile_t        	 *input;
      wfa_t            	 *wfa;
      video_t          	 *video;
      const d_options_t  *dop;
      dfiasco_t	       	 *dfiasco;
      fiasco_decoder_t 	 *decoder;
      fiasco_d_options_t *default_options = NULL;

      if (options)
      {
	 dop = cast_d_options ((fiasco_d_options_t *) options);
	 if (!dop)
	    return NULL;
      }
      else
      {
	 default_options = fiasco_d_options_new ();
	 dop 		 = cast_d_options (default_options);
      }

      wfa   = alloc_wfa (NO);
      video = alloc_video (NO);
      input = open_wfa (filename, wfa->wfainfo);
      read_basis (wfa->wfainfo->basis_name, wfa);

      decoder 	       	   = fiasco_calloc (1, sizeof (fiasco_decoder_t));
      decoder->delete  	   = fiasco_decoder_delete;
      decoder->write_frame = fiasco_decoder_write_frame;
      decoder->get_frame   = fiasco_decoder_get_frame;
      decoder->get_length  = fiasco_decoder_get_length;
      decoder->get_rate    = fiasco_decoder_get_rate;
      decoder->get_width   = fiasco_decoder_get_width;
      decoder->get_height  = fiasco_decoder_get_height;
      decoder->get_title   = fiasco_decoder_get_title;
      decoder->get_comment = fiasco_decoder_get_comment;
      decoder->is_color    = fiasco_decoder_is_color;

      decoder->private = dfiasco
		       = alloc_dfiasco (wfa, video, input,
					dop->magnification,
					dop->smoothing,
					dop->image_format);

      if (default_options)
	 fiasco_d_options_delete (default_options);
      if (dfiasco->enlarge_factor >= 0)
      {
	 int 	       n;
	 unsigned long pixels = wfa->wfainfo->width * wfa->wfainfo->height;

	 for (n = 1; n <= (int) dfiasco->enlarge_factor; n++)
	 {
	    if (pixels << (n << 1) > 2048 * 2048)
	    {
	       set_error (_("Magnifaction factor `%d' is too large. "
			    "Maximium value is %d."),
			  dfiasco->enlarge_factor, max (0, n - 1));
	       fiasco_decoder_delete (decoder);
	       return NULL;
	    }
	 }
      }
      else
      {
	 int n;

	 for (n = 0; n <= (int) - dfiasco->enlarge_factor; n++)
	 {
	    if (wfa->wfainfo->width >> n < 32
		|| wfa->wfainfo->height >> n < 32)
	    {
	       set_error (_("Magnifaction factor `%d' is too small. "
			    "Minimum value is %d."),
			  dfiasco->enlarge_factor, - max (0, n - 1));
	       fiasco_decoder_delete (decoder);
	       return NULL;
	    }
	 }
      }
      return (fiasco_decoder_t *) decoder;
   }
   catch
   {
      return NULL;
   }
}
