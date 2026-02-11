IIT_find_linear (T this, char *label) {
  int i;
  char *p;

  for (i = 0; i < this->total_nintervals; i++) {
#ifdef WORDS_BIGENDIAN
#ifdef HAVE_64_BIT
    if (this->label_pointers_8p == true) {
      p = &(this->labels[Bigendian_convert_uint8(this->labelpointers8[i])]);
    } else {
      p = &(this->labels[Bigendian_convert_uint(this->labelpointers[i])]);
    }
#else
    p = &(this->labels[Bigendian_convert_uint(this->labelpointers[i])]);
#endif
#else
#ifdef HAVE_64_BIT
    if (this->label_pointers_8p == true) {
      p = &(this->labels[this->labelpointers8[i]]);
    } else {
      p = &(this->labels[this->labelpointers[i]]);
    }
#else
    p = &(this->labels[this->labelpointers[i]]);
#endif
#endif
    while (isspace((int) *p)) {
      p++;
    }
    if (!strcmp(label,p)) {
      return i + 1;
    }
  }

  return -1;
}
