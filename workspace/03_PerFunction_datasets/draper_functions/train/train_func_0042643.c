md5_sig_to_string(void *signature, char *str, const int str_len)
{
  unsigned char	*sig_p;
  char		*str_p, *max_p;
  unsigned int	high, low;

  str_p = str;
  max_p = str + str_len;

  for (sig_p = (unsigned char *)signature;
       sig_p < (unsigned char *)signature + MD5_SIZE;
       sig_p++) {
    high = *sig_p / 16;
    low = *sig_p % 16;

    if (str_p + 1 >= max_p) {
      break;
    }
    *str_p++ = HEX_STRING[high];
    *str_p++ = HEX_STRING[low];
  }

  if (str_p < max_p) {
    *str_p++ = '\0';
  }
}
