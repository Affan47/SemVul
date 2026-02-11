replicate_color(int depth, mono_fill_chunk color)
{
    switch (depth) {

      case 1:
        color = (mono_fill_chunk)(-(int)color); break;

      case 2:
        color = fill_pat_2[color]; break;

      case 4:
        color = fill_pat_4[color]; break;

      case 8:
        color= mono_fill_make_pattern(color); break;

#if mono_fill_chunk_bytes > 2
      case 16:
        color = (color << 16) | color;

#endif
#if mono_fill_chunk_bytes > 4
      case 32:
        color = (color << 32) | color;
        break;
#endif
    }

    return color;
}
