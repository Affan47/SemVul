cgmcomhead(unsigned char *es, int elemclass, int id, int len)
{


  int temp;

  if (!es)
    {
    return 0;
    }


  *es = static_cast<unsigned char>(elemclass) << 4;

  temp = 0177 & id ;
  temp = temp >> 3;
  *es = *es | temp;
  es++;
  id = id << 5;
  *es = static_cast<unsigned char>(id);
  *es = *es | static_cast<unsigned char>( 037 & len );

  return 1;
}
