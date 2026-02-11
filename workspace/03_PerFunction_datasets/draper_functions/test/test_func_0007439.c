init (pt_lkdins, pt_mem)

struct lkdins *pt_lkdins;
unsigned char *pt_mem   ;

  {
  char         *name          ;
  char          fil_name [128];
  unsigned int  fil_addr      = 0;
  unsigned int  fil_byte      = 0;
  FILE         *fp            ;
  unsigned int  cur_adr       = 0;
  unsigned int  cur_val       = 0;
  unsigned int  red_c         = 0;
  unsigned int  red_val       = 0;
  unsigned int  state         = READ_ADR;

  name = (char *)vhx_GetInstanceName (pt_lkdins);

  splitname (name, fil_name, &fil_addr, &fil_byte);

  if ((fp = mbkfopen (fil_name, "ini", READ_TEXT)) == NULL)
    {
    fprintf (stderr, "cannot open RAM initialization file: %s.ini\n", fil_name);
    exit (1);
    }

  printf ("loading RAM initialization file: %s.ini , %.8x , %d\n",
          fil_name, fil_addr, fil_byte);


  while ((red_c = fgetc (fp)) != EOF)
    {
    switch (red_c)
      {
      case ' ' :
      case '\t':
        break;

      case '\n':
        if (((cur_adr & ADR_MASK) == fil_addr) &&
            ((cur_adr & BYT_MASK) == fil_byte)   )
          pt_mem [(cur_adr & (~ADR_MASK)) >> 2] = cur_val;

        state   = READ_ADR;
        cur_adr = 0;
        cur_val = 0;
        break;

      case ':' :
        state = READ_VAL;
        break;

      default  :
        if ((red_c >= '0') && (red_c <= '9'))
          red_val = red_c - '0';
        if ((red_c >= 'a') && (red_c <= 'f'))
          red_val = red_c - 'a' + 10;
        if ((red_c >= 'A') && (red_c <= 'F'))
          red_val = red_c - 'A' + 10;

        if (state == READ_ADR)
          cur_adr = (cur_adr << 4) + red_val;
        else
          cur_val = (cur_val << 4) + red_val;
      }
    }

  fclose (fp);
  }
