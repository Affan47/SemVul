Remap_general_lowlevel(byte * conversion_table,byte * in_buffer, byte *out_buffer,short width,short height,short buffer_width)
{
  int dx,cx;


  for(dx=height;dx>0;dx--)
  {

    for(cx=width;cx>0;cx--)
    {
      *out_buffer = conversion_table[*in_buffer];
      in_buffer++;
      out_buffer++;
    }
    in_buffer += buffer_width-width;
    out_buffer += buffer_width-width;
  }
}
