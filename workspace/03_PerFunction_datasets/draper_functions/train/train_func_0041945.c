getorders()
{
  unsigned char poscnt;


  for(poscnt=0;poscnt<51;poscnt++)
    if(song[poscnt] == 0xff)
      break;

  return poscnt;
}
