ppc32_load_bat_array(cpu_ppc_t *cpu,struct ppc32_bat_prog *bp)
{
   while(bp->index != -1) {
      ppc32_set_bat(cpu,bp);
      bp++;
   }
}
