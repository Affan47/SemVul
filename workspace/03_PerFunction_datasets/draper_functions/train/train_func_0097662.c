do_grid_render (struct thread_grid_render *params)
{

    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char *p_out;
    short *p_int16;
    unsigned short *p_uint16;
    int *p_int32;
    unsigned int *p_uint32;
    float *p_float;
    double *p_double;
    double value;
    int x;

    if (params->sample_format == GGRAPH_SAMPLE_FLOAT)
      {
	  if (params->bits_per_sample == 32)
	    {
		p_float = (float *) (params->pixels);
		p_float += params->base;
	    }
	  else
	    {
		p_double = (double *) (params->pixels);
		p_double += params->base;
	    }
      }
    if (params->sample_format == GGRAPH_SAMPLE_INT)
      {
	  if (params->bits_per_sample == 32)
	    {
		p_int32 = (int *) (params->pixels);
		p_int32 += params->base;
	    }
	  else
	    {
		p_int16 = (short *) (params->pixels);
		p_int16 += params->base;
	    }
      }
    if (params->sample_format == GGRAPH_SAMPLE_UINT)
      {
	  if (params->bits_per_sample == 32)
	    {
		p_uint32 = (unsigned int *) (params->pixels);
		p_uint32 += params->base;
	    }
	  else
	    {
		p_uint16 = (unsigned short *) (params->pixels);
		p_uint16 += params->base;
	    }
      }
    p_out = params->p_rgb + (params->base * 3);
    for (x = 0; x < params->num_pixels; x++)
      {
	  if (params->sample_format == GGRAPH_SAMPLE_FLOAT)
	    {
		if (params->bits_per_sample == 32)
		    value = *p_float++;
		else
		    value = *p_double++;
	    }
	  if (params->sample_format == GGRAPH_SAMPLE_INT)
	    {
		if (params->bits_per_sample == 32)
		    value = *p_int32++;
		else
		    value = *p_int16++;
	    }
	  if (params->sample_format == GGRAPH_SAMPLE_UINT)
	    {
		if (params->bits_per_sample == 32)
		    value = *p_uint32++;
		else
		    value = *p_uint16++;
	    }
	  match_color (params->color_map, value, params->no_data_value, &red,
		       &green, &blue);
	  *p_out++ = red;
	  *p_out++ = green;
	  *p_out++ = blue;
      }
}
