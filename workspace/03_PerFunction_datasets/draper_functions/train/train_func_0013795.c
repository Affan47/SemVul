get_all_picture_numbers()
{
  uint16_t *result;
  int image_index;

  if (mg1_file == NULL)
    return NULL;

  if ((result = (uint16_t*)malloc(sizeof(uint16_t) * header.nof_images))
      == NULL)
    return NULL;

  for (image_index = 0; image_index < header.nof_images; image_index++)
  {
    result[image_index] = mg1_image_entries[image_index].number;
  }

  return result;
}
