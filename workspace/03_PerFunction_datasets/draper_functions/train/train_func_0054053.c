compile_sprunish (const a_pixel *src, a_pixel transp_color,
		  a_pixel glenz_color, a_pixel *glenz_line,
		  a_pixel opaque_color,
		  unsigned int block_height,
		  unsigned int block_width,
		  unsigned int src_width, unsigned int dest_width)
{
  a_sprite* sprite;
  unsigned int row;
  unsigned int code_size;
  a_u8 *pc;


  code_size = block_height * ((block_width / 2 + 1) * 3 + 3);

  XMALLOC_VAR (sprite);
  XMALLOC_ARRAY (sprite->unish.code, code_size);


  pc = sprite->unish.code;
  for (row = block_height; row; --row) {
    unsigned int m, n, s;
    const a_pixel *eol = src + block_width;


    do {

      for (m = 0; src < eol && m < 255 && *src == transp_color; ++src)
	++m;

      for (n = 0; src < eol && n < 255
	     && *src != transp_color && *src != glenz_color; ++src)
	++n;

      for (s = 0; src < eol && s < 255 && *src == glenz_color; ++src)
	++s;

      *pc++ = m;      *pc++ = n;
      *pc++ = s;

    } while (src < eol);

    *pc++ = 0;
    *pc++ = 0;
    *pc++ = 0;


    src += src_width - block_width;
  }

  sprite->unish.kind = S_RLE_UNIC_SHADE;
  sprite->unish.draw = draw_sprunish;
  sprite->unish.end_code = pc;
  sprite->unish.line_skip = dest_width - block_width;
  sprite->unish.glenz = glenz_line;
  sprite->unish.color = opaque_color;

  assert (pc < sprite->unish.code + code_size);

  return sprite;
}
