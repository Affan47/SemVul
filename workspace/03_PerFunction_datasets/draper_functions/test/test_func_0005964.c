ccf_true_true_to_8_true_conversion_table(
  cct_true_true_conversion_table true_true,
  int map_size,
  unsigned char *colormaps[3])
{
  cct_8_true_conversion_table answer;
  int i, rgb;

  answer = (cct_8_true_conversion_table)
    calloc(1, sizeof(struct ccs_8_true_conversion_table));

  for (i = 0; i < map_size; i++)
  {
    for (rgb = 0; rgb < 3; rgb ++)
    {
      answer->pixel_values[i] +=
        true_true->pixel_values[rgb][colormaps[rgb][i]];
    }
  }
  return answer;
}
