comba_negate(_MIPD_ big x,big w)
{
    unsigned int i;
    big modulus;
    mr_small *a,*b,*c;
    mr_small carry,su;
#ifdef MR_WIN64
    mr_small ma,mb,u;
#endif
#ifdef MR_ITANIUM
    mr_small ma,u;
#endif
#ifdef MR_NOASM
    mr_large u;
#endif

#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    modulus=mr_mip->modulus;
    if (w!=x)
    {
        for (i=MR_COMBA;i<(w->len&MR_OBITS);i++) w->w[i]=0;

    }
    a=modulus->w; b=x->w; c=w->w;


  ASM (
  "movq %0,%%rsi\n"
  "movq %1,%%rbx\n"
  "movq %3,%%rdi\n"
  "movq (%%rsi),%%rax\n"
  "subq (%%rbx),%%rax\n"
  "movq %%rax,(%%rdi)\n"
  "movq 8*1(%%rsi),%%rax\n"
  "sbbq 8*1(%%rbx),%%rax\n"
  "movq %%rax,8*1(%%rdi)\n"
  "movq 8*2(%%rsi),%%rax\n"
  "sbbq 8*2(%%rbx),%%rax\n"
  "movq %%rax,8*2(%%rdi)\n"
  "movq 8*3(%%rsi),%%rax\n"
  "sbbq 8*3(%%rbx),%%rax\n"
  "movq %%rax,8*3(%%rdi)\n"
  "movq $0,%%rax\n"
  "adcq %%rax,%%rax\n"
  "movq %%rax,%2\n"
   :
   :"m"(a),"m"(b),"m"(carry),"m"(c)
   :"rax","rdi","rsi","rbx","memory"
  );

    w->len=MR_COMBA;
    if (w->w[MR_COMBA-1]==0) mr_lzero(w);
}
