cgmSetFillHatch(cgmImagePtr im, int inhatch)
{


  unsigned char *es, *esp;
  int octet_count, temp;


  if (inhatch == -1)
    {
    return 1;
    }


  if (inhatch == im->shapehatch)
    {
    return 1;
    }


  if ((inhatch < 1) || (inhatch > 6))
    {
    return 0;
    }


  es = static_cast<unsigned char *>(calloc(4*4, SIZEOF(unsigned char ) ));
  if (!es)
    {
    return 0;
    }
  esp=es;


  if (!cgmcomhead (es, 5, 24, 2))
    {
    free(esp);
    return 0;
    }
  es += 2;


  temp = inhatch >> 8;
  *es = *es | (temp & 0377);
  es++;
  *es = *es | (inhatch & 0377);
  es++;

  octet_count = 4;


  if (cgmAddElem(im, esp, octet_count))
    {
    im->shapehatch = static_cast<short int>(inhatch);
    free(esp);
    return 1;
    }
  else
    {
    free(esp);
    return 0;
    }
}
