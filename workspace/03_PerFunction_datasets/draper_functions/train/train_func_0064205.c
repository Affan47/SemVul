cgmSetTextPath(cgmImagePtr im, int tpath)
{


  unsigned char *es, *esp;
  int octet_count;


  if (tpath == -1)
    {
    return 1;
    }


  if (tpath == im->textpath)
    {
    return 1;
    }


  es = static_cast<unsigned char *>( calloc(4*4, SIZEOF(unsigned char ) ));
  if (!es)
    {
    return 0;
    }
  esp=es;

  if (!cgmcomhead(es, 5, 17, 2))
    {
    free(esp);
    return 0;
    }
  es +=2; octet_count = 2;

  es += cgmAppShort(es, static_cast<short int>(tpath));
  octet_count += 2;


  if (cgmAddElem(im, esp, octet_count))
    {
    im->textpath = static_cast<short int>(tpath);
    free(esp);
    return 1;
    }
  else
    {
    free(esp);
    return 0;
    }
}
