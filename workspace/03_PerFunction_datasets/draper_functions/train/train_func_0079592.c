greyscale(v)
vari *v;
{ INT i, j0, j1;
  j0 = getcolidx(getargval(v,"lo",1),0);
  j1 = getcolidx(getargval(v,"hi",1),1);
  for (i=0; i<=10; i++)
    AC("",((10-i)*mycol[j0].r+i*mycol[j1].r)/11,
          ((10-i)*mycol[j0].g+i*mycol[j1].g)/11,
          ((10-i)*mycol[j0].b+i*mycol[j1].b)/11,8+i);
}
