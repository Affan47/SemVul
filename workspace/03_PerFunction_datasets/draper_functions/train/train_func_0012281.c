vncEncryptAndStorePasswd (char *passwd, char *fname)
{
  FILE *fp;
  uint32_t i;
  unsigned char encryptedPasswd[8];

  if ((fp = fopen (fname, "w")) == NULL)
    return 1;

  chmod (fname, S_IRUSR | S_IWUSR);


  for (i = 0; i < 8; i++) {
    if (i < strlen (passwd)) {
      encryptedPasswd[i] = passwd[i];
    } else {
      encryptedPasswd[i] = 0;
    }
  }


  deskey (fixedkey, EN0);
  des (encryptedPasswd, encryptedPasswd);

  for (i = 0; i < 8; i++) {
    putc (encryptedPasswd[i], fp);
  }

  fclose (fp);
  return 0;
}
