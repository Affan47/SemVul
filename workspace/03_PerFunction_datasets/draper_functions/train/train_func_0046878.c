scanStringForImageExtensionsFastJPGOnly(char * inpt)
{
  if (inpt==0) { return 0; }
  unsigned int length = strlen(inpt);
  if (length<3) { return 0; }


  char * inptPTR = inpt;
  char * inptLimit = inpt+length;


  while (inptPTR<inptLimit)
  {
    switch (*inptPTR)
     {
       case 'j' :
       case 'J' :
        if (inptPTR+2>=inptLimit)  {  return 0; }
        switch (*(inptPTR+1))
        {
          case 'p' :
          case 'P' :
          switch (*(inptPTR+2))
          {
           case 'g' :
           case 'G' :

             return 1;
           break;
          }
          break;
        }
       break;
     }

    ++inptPTR;
  }
 return 0;
}
