exif_read_double(const exif_tag_t* tag, const int index)
{
  unsigned int num, den;
  gbint32* data = (gbint32*)tag->data;

  num = data[index * 2];
  den = data[(index * 2) + 1];
  if (den == 0) {
    den = 1;
  }

  return (double)num / (double)den;
}
