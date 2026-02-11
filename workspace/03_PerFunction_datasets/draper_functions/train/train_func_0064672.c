psTextDim(f,z,w,h)
INT f, *w, *h;
char *z;
{ if (f==1)
  { *w = (INT)(10*strlen(z)*dpp);
    *h = (INT)(18*dpp);
  }
  else
  { *w = (INT)(8*strlen(z)*dpp);
    *h = (INT)(12*dpp);
  }
}
