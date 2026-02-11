fat32_direntry_short_name(const struct fat32_direntry_t *direntry)
{
  const uint8_t *p = direntry->name + (FAT32_DIRENTRY_NAME_SIZE - 1);
  size_t base_name_size = 0;
  size_t ext_size       = 0;

  for (int i = 0; i < FAT32_DIRENTRY_EXTENSION_SIZE; i++, p--) {
    if (*p != SPACE) {
      ext_size += FAT32_DIRENTRY_EXTENSION_SIZE - i;
      break;
    }
  }

  p = direntry->name + FAT32_DIRENTRY_BASE_NAME_SIZE - 1;

  for (int i = 0; i < FAT32_DIRENTRY_BASE_NAME_SIZE; i++, p--) {
    if (*p != SPACE) {
      base_name_size += FAT32_DIRENTRY_BASE_NAME_SIZE - i;
      break;
    }
  }


  size_t name_size = base_name_size + ext_size + 1;
  if (ext_size != 0) {

    name_size += 1;
  }

  char *result = malloc(name_size);
  if (result == NULL) {
    return NULL;
  }
  result[name_size - 1] = '\0';

  memcpy(result, direntry->name, base_name_size);

  if (ext_size != 0) {
    result[base_name_size] = '.';
    memcpy(result + base_name_size + 1,
           direntry->name + FAT32_DIRENTRY_BASE_NAME_SIZE,
           ext_size);
  }

  return result;
}
