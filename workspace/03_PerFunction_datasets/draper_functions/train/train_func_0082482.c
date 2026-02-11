iTIFFExpandComplexInt(void* line_buffer, int count, int cpx_int)
{
  count *= 2;


  if (cpx_int == 1)
  {

    short* short_buffer = (short*)line_buffer;
    float* float_buffer = (float*)line_buffer;

    float_buffer += count-1;
    short_buffer += count-1;

    for (int i = 0; i < count; i++)
      *float_buffer-- = (float)(*short_buffer--);
  }
  else
  {

    int*   int_buffer   = (int*)line_buffer;
    float* float_buffer = (float*)line_buffer;

    for (int i = 0; i < count; i++)
      *float_buffer++ = (float)(*int_buffer++);
  }
}
