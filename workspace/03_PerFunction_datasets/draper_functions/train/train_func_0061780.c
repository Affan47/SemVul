GetOrder(const char* str, PRUint32 *charLen)
{

  if ((unsigned char)*str >= (unsigned char)0x81 && (unsigned char)*str <= (unsigned char)0x9f ||
      (unsigned char)*str >= (unsigned char)0xe0 && (unsigned char)*str <= (unsigned char)0xfc )
      *charLen = 2;
  else
      *charLen = 1;


  if (*str == '\202' &&
        (unsigned char)*(str+1) >= (unsigned char)0x9f &&
        (unsigned char)*(str+1) <= (unsigned char)0xf1)
    return (unsigned char)*(str+1) - (unsigned char)0x9f;
  return -1;
}
