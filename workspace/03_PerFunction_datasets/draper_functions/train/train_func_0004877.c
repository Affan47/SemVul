usbtiny_chip_erase(PROGRAMMER * pgm, AVRPART * p)
{
  unsigned char res[4];

  if (p->op[AVR_OP_CHIP_ERASE] == NULL) {
    fprintf(stderr, "Chip erase instruction not defined for part \"%s\"\n",
            p->desc);
    return -1;
  }


  if (! usbtiny_avr_op( pgm, p, AVR_OP_CHIP_ERASE, res )) {
    return -1;
  }
  usleep( p->chip_erase_delay );


  pgm->initialize(pgm, p);

  return 0;
}
