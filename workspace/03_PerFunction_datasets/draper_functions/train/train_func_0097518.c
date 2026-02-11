_scan_for_start_code (const guint8 * data, guint offset, guint size)
{
  guint i = 0;

  while (i <= (size - 4)) {
    if (data[i + 2] > 1) {
      i += 3;
    } else if (data[i + 1]) {
      i += 2;
    } else if (data[i] || data[i + 2] != 1) {
      i++;
    } else {
      break;
    }
  }

  if (i <= (size - 4))
    return i + offset;


  return -1;
}
