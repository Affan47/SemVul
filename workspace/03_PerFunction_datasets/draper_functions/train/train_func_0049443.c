Sequence_print (FILE *fp, T this, bool uppercasep, int wraplength, bool trimmedp) {
  int i = 0, pos, start, end;
  char uppercaseCode[128] = UPPERCASE_STD;

  if (trimmedp == true) {
    start = this->trimstart;
    end = this->trimend;
  } else {
    start = 0;
    end = this->fulllength;
  }

  if (uppercasep == true) {
    for (pos = start; pos < end; pos++, i++) {
      putc(uppercaseCode[(int) this->contents[i]],fp);
      if ((i+1) % wraplength == 0) {
	putc('\n',fp);
      }
    }
  } else {
    for (pos = start; pos < end; pos++, i++) {
      putc(this->contents[i],fp);
      if ((i+1) % wraplength == 0) {
	putc('\n',fp);
      }
    }
  }
  if (i % wraplength != 0) {
    putc('\n',fp);
  }
  return;
}
