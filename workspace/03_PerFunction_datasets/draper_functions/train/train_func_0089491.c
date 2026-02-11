img_read_mar300data (img_handle img, FILE *file, int *org_data)
{
  int x, y, little;

  unsigned char *data, *cdata;


  if (img_set_dimensions (img, org_data [0], org_data [1]))

    return img_BAD_FORMAT;

  if (img->size [0] == 0 ||
      img->size [1] == 0)

    return 0;


  little = org_data [5];

  x = 1;

  if (*((char *) &x) == 0)

    little = !little;

  data = (unsigned char *) malloc (org_data [2]);

  if (!data)

    return img_BAD_ALLOC;

  for (x = 0; x < img_columns (img); x++) {

    if (fread (data, org_data [2], 1, file) == 0)
    {
      free (data);

      return img_BAD_READ;
    }

    cdata = data;

    for (y = 0; y < img_rows (img); y++, cdata += 2)

     *(img_pixelptr (img, x, y)) = (int) cdata [little] + ((int) cdata [1 - little] << 8);

    }

  free (data);


  for (; org_data [4] > 0; org_data [4]--)
  {
    int O [2], c;

    for (c = 0; c < 2; c++)
    {
      if (img_read_i4 (file, &O [c]))

        return img_BAD_READ;

      if (org_data [5])

        O [c] = img_swap_i4 (O [c]);
    }

    x = (O [0] - 1) / img_rows (img);
    y = (O [0] - 1) % img_rows (img);

    if (x >= 0 && x < img_columns (img) &&
        y >= 0 && y < img_rows (img))

      *(img_pixelptr (img, x, y)) = O [1];

    else

      return img_BAD_FORMAT;
  }

  return 0;
}
