writeline (FILE *dst, uint8* buffer, int bytes) {
  uint8 value, count, tmp;
  uint8 *finish = buffer + bytes;

  while (buffer < finish) {

    value = *(buffer++);
    count = 1;

    while (buffer < finish && count < 63 && *buffer == value) {
      count++; buffer++;
    }

    if (value < 0xc0 && count == 1) {
      fputc(value, dst);
    } else {
      tmp = count + 0xc0;
      fputc(tmp, dst);
      fputc(value, dst);
    }
  }
}
