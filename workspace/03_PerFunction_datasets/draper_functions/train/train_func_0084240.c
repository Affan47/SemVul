socket_receive_file_to_buff (int fd, int *size)
{


  static const char file_stuff_key[] = "ft_StUfF_key";
  char *buff;
  int bufflen;
  int n, k, i;
  char c;

  bufflen = 1024;
  buff = (char *) g_malloc (bufflen);
  *size = 0;

  for (k = 0; file_stuff_key[k] != '\0';) {
    n = read (fd, &c, 1);
    if (n == 0)
      break;

    if ((*size) + k + 1 >= bufflen) {

      bufflen += bufflen / 4;
      buff = (char *) g_realloc (buff, bufflen);
    }
    if (file_stuff_key[k] == c)
      k++;
    else if ((c == 'X') && (file_stuff_key[k + 1] == '\0')) {

      for (i = 0; i < k; i++, (*size)++)
        buff[*size] = file_stuff_key[i];
      k = 0;

    } else {
      for (i = 0; i < k; i++, (*size)++)
        buff[*size] = file_stuff_key[i];
      k = 0;
      buff[*size] = c;
      (*size)++;
    }
  }

  return buff;
}
