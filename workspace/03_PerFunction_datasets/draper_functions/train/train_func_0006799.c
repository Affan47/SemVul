poll_padlock (void (*add)(const void*, size_t, enum random_origins),
              enum random_origins origin, int fast)
{
  volatile char buffer[64+8] __attribute__ ((aligned (8)));
  volatile char *p;
  unsigned int nbytes, status;


  p = buffer;
  nbytes = 0;
  while (nbytes < 64)
    {
#if defined(__x86_64__) && defined(__LP64__)
      asm volatile
        ("movq %1, %%rdi\n\t"
         "xorq %%rdx, %%rdx\n\t"
         ".byte 0x0f, 0xa7, 0xc0\n\t"
         : "=a" (status)
         : "g" (p)
         : "%rdx", "%rdi", "cc"
         );
#else
      asm volatile
        ("movl %1, %%edi\n\t"
         "xorl %%edx, %%edx\n\t"
         ".byte 0x0f, 0xa7, 0xc0\n\t"
         : "=a" (status)
         : "g" (p)
         : "%edx", "%edi", "cc"
         );
#endif
      if ((status & (1<<6))
          && !(status & (1<<13))
          && !(status & (1<<14))
          && !(status & 0x1c00)
          && (!(status & 0x1f) || (status & 0x1f) == 8)
          )
        {
          nbytes += (status & 0x1f);
          if (fast)
            break;
          p += (status & 0x1f);
        }
      else
        {


          rng_failed = 1;
          break;
        }
    }

  if (nbytes)
    {
      (*add) ((void*)buffer, nbytes, origin);
      wipememory (buffer, nbytes);
    }
  return nbytes;
}
