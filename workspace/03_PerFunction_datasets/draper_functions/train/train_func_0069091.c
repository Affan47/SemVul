stk500v2_initialize(PROGRAMMER * pgm, AVRPART * p)
{

  if ((PDATA(pgm)->pgmtype == PGMTYPE_STK600 ||
       PDATA(pgm)->pgmtype == PGMTYPE_AVRISP_MKII ||
       PDATA(pgm)->pgmtype == PGMTYPE_JTAGICE_MKII) != 0
      && (p->flags & (AVRPART_HAS_PDI | AVRPART_HAS_TPI)) != 0) {


    if ((p->flags & AVRPART_HAS_PDI) != 0) {


      AVRMEM *bootmem = avr_locate_mem(p, "boot");
      AVRMEM *flashmem = avr_locate_mem(p, "flash");
      if (bootmem == NULL || flashmem == NULL) {
        fprintf(stderr,
                "%s: stk500v2_initialize(): Cannot locate \"flash\" and \"boot\" memories in description\n",
                progname);
      } else {
        PDATA(pgm)->boot_start = bootmem->offset - flashmem->offset;
      }
    }
    stk600_setup_xprog(pgm);
  } else {
    stk600_setup_isp(pgm);
  }

  if (p->flags & AVRPART_IS_AT90S1200) {


    pgm->disable(pgm);
    usleep(10000);
  }

  return pgm->program_enable(pgm, p);
}
