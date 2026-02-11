isFullyOpaque(const unsigned char* image, unsigned w, unsigned h, const LodePNG_InfoColor* info)
{


  unsigned i, numpixels = w * h;
  if(info->colorType == 6)
  {
    if(info->bitDepth == 8)
    {
      for(i = 0; i < numpixels; i++) if(image[i * 4 + 3] != 255) return 0;
    }
    else
    {
      for(i = 0; i < numpixels; i++) if(image[i * 8 + 6] != 255 || image[i * 8 + 7] != 255) return 0;
    }
    return 1;
  }
  else if(info->colorType == 4)
  {
    if(info->bitDepth == 8)
    {
      for(i = 0; i < numpixels; i++) if(image[i * 2 + 1] != 255) return 0;
    }
    else
    {
      for(i = 0; i < numpixels; i++) if(image[i * 4 + 2] != 255 || image[i * 4 + 3] != 255) return 0;
    }
    return 1;
  }
  else if(info->colorType == 3)
  {

    return(isPaletteFullyOpaque(info->palette, info->palettesize));
  }

  return 0;
}
