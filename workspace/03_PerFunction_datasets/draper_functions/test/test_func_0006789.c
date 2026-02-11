put_num(long int num, int f, int bytes)
{
  unsigned int i;
  unsigned char c;

  for (i=0; bytes--; i++) {
    c = (num >> (i<<3)) & 0xff;
    if (write(f, &c, 1)==-1) {
      perror("Could not write to output.");
      exit(1);
    }
  }
}
