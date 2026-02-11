compute_planar_coefficients (Genesys_Device * dev,
			     uint8_t * shading_data,
			     unsigned int factor,
			     unsigned int pixels_per_line,
			     unsigned int words_per_color,
			     unsigned int channels,
			     unsigned int cmat[3],
			     unsigned int offset,
			     unsigned int coeff,
			     unsigned int target)
{
  uint8_t *ptr;
  uint32_t x, c, i;
  uint32_t val, dk, br;

  DBG (DBG_io,
       "compute_planar_coefficients: factor=%d, pixels_per_line=%d, words=0x%X, coeff=0x%04x\n", factor,
       pixels_per_line, words_per_color, coeff);
  for (c = 0; c < channels; c++)
    {

      for (x = 0; x < pixels_per_line; x+=factor)
	{


	  ptr = shading_data + words_per_color * cmat[c] * 2 + (x + offset) * 4;

	  dk = 0;
	  br = 0;


	  for(i=0;i<factor;i++)
	  {
	  dk +=
	    256 * dev->dark_average_data[((x+i) + pixels_per_line * c) * 2 + 1];
	  dk += dev->dark_average_data[((x+i) + pixels_per_line * c) * 2];
	  br +=
	    256 * dev->white_average_data[((x+i) + pixels_per_line * c) * 2 + 1];
	  br += dev->white_average_data[((x+i) + pixels_per_line * c) * 2];
	  }
	  dk /= factor;
	  br /= factor;

	  val = compute_coefficient (coeff, target, br - dk);


	  for (i = 0; i < factor; i++)
	    {
	      ptr[0 + 4 * i] = dk & 255;
	      ptr[1 + 4 * i] = dk / 256;
	      ptr[2 + 4 * i] = val & 0xff;
	      ptr[3 + 4 * i] = val / 256;
	    }
	}
    }


  if(channels==1)
  {
	  memcpy(shading_data+cmat[1]*2*words_per_color,
	         shading_data+cmat[0]*2*words_per_color,
		 words_per_color*2);
	  memcpy(shading_data+cmat[2]*2*words_per_color,
	         shading_data+cmat[0]*2*words_per_color,
		 words_per_color*2);
  }
}
