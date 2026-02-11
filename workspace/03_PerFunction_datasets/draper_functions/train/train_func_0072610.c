writepbm(char *nam,pix *p){
  FILE *f1;int x,y,a,b,dx,i;
  dx=(p->x+7)&~7;
  for(y=0;y<p->y;y++)
  for(x=0;x<p->x;x++){
    a=(x+y*dx)>>3;b=7-(x&7);
    i=x+y*p->x;
    if(p->bpp==3) i=(p->p[3*i+0]+p->p[3*i+1]+p->p[3*i+2])/3;
    else          i= p->p[  i  ];
    i=((i>127)?0:1);
    p->p[a]=(p->p[a] & (~1<<b)) | (i<<b);
  }
  f1=fopen(nam,"wb");if(!f1)F0("open");
  fprintf(f1,"P4\n%d %d\n",p->x,p->y);
  if(p->y!=(int)fwrite(p->p,dx>>3,p->y,f1))F0("write");
  fclose(f1);
  return 0;
}
