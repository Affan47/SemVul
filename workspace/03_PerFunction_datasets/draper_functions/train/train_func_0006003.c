_0d_write(K a,K b)
{
  I t=b->t, n=b->n;
  K k;

  P(!ok_0dw(b),TE)

  S m=CSK(a);

  I s=0;

  if(3==ABS(t))s=n;
  else DO(n,s+=1+kK(b)[i]->n)

  I f=m[0]?open(m,O_RDWR|O_CREAT|O_TRUNC,07777):1;
  P(f<0,DOE)

  if(1==f)
  {
    if(3==ABS(t)) write(f,kC(b),s);
    else DO(n, k=kK(b)[i]; if(3==ABS(k->t))write(f,kC(k),k->n); write(f,"\n",1); )
  }
  else
  {
    P(ftruncate(f,s),SE)


    S v;
    if(MAP_FAILED==(v=mmap(0,s,PROT_WRITE,MAP_SHARED,f,0)))R SE;

    close(f);

    I c=0;
    if(3==ABS(t)) memcpy(v,kC(b),s);
    else DO(n, k=kK(b)[i]; if(3==ABS(k->t)){memcpy(v+c,kC(k),k->n); c+=k->n;} v[c++]='\n'; )

    msync(v,s,MS_SYNC|MS_INVALIDATE);
    munmap(v,s);
  }

  R _n();
}
