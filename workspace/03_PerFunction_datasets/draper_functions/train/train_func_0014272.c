do_padlock (const RIJNDAEL_context *ctx, int decrypt_flag,
            unsigned char *bx, const unsigned char *ax)
{


  unsigned char a[16] __attribute__ ((aligned (16)));
  unsigned char b[16] __attribute__ ((aligned (16)));
  unsigned int cword[4] __attribute__ ((aligned (16)));
  int blocks;


  cword[0] = (ctx->rounds & 15);
  cword[1] = 0;
  cword[2] = 0;
  cword[3] = 0;
  if (decrypt_flag)
    cword[0] |= 0x00000200;

  memcpy (a, ax, 16);

  blocks = 1;
#ifdef __x86_64__
  asm volatile
    ("pushfq\n\t"
     "popfq\n\t"
     ".byte 0xf3, 0x0f, 0xa7, 0xc8\n\t"
     :
     : "S" (a), "D" (b), "d" (cword), "b" (ctx->padlockkey), "c" (blocks)
     : "cc", "memory"
     );
#else
  asm volatile
    ("pushfl\n\t"
     "popfl\n\t"
     "xchg %3, %%ebx\n\t"
     ".byte 0xf3, 0x0f, 0xa7, 0xc8\n\t"
     "xchg %3, %%ebx\n"
     :
     : "S" (a), "D" (b), "d" (cword), "r" (ctx->padlockkey), "c" (blocks)
     : "cc", "memory"
     );
#endif

  memcpy (bx, b, 16);

}
