dns_random_init(const char data[128])
{
  int i;
  struct taia t;
  char tpack[16];

  for (i = 0;i < 32;++i)
    uint32_unpack(data + 4 * i,seed + i);

  taia_now(&t);
  taia_pack(tpack,&t);
  for (i = 0;i < 4;++i)
    uint32_unpack(tpack + 4 * i,in + 4 + i);

  in[8] = getpid();
  in[9] = getppid();

}
