write_back_cell(struct text_trie *tt, struct cell *c, int idx)
{
  int i;
  char buf[LINE_LEN+1];

  if (((anthy_mmap_size(tt->mapping) / LINE_LEN) < (idx + 1)) ||
      idx < 0) {
    return ;
  }
  for (i = 0; i < LINE_LEN; i++) {
    buf[i] = ' ';
  }
  encode_cell(c, buf);
  buf[LINE_LEN-1] = '\n';
  if (anthy_mmap_is_writable(tt->mapping)) {
    memcpy(&tt->ptr[idx*LINE_LEN], buf, LINE_LEN);
  } else {
    fseek(tt->wfp, idx*LINE_LEN, SEEK_SET);
    fwrite(buf, LINE_LEN, 1, tt->wfp);
    fflush(tt->wfp);
  }
}
