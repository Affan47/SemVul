hexdump		(const char	*str,
		 const void	*data,
		 unsigned int	len)
{
  const uint8_t	*p = data;
  unsigned int	i;

  printf("- %s -\n", str);
  for (i = 0; i < len; i++)
    printf("0x%02x,%c", p[i], (i+1)%16 ? ' ' : '\n');
  puts("");
}
