dmp_tchks(FILE *f, register struct tchk_t *tcp)
{
 char s1[RECLEN];

 for (; tcp != NULL; tcp = tcp->tchknxt)
  {

   if (tcp->tc_gone || tcp->tc_supofsuphld || tcp->tc_recofrecrem) continue;

   __wrap_puts(__to_tcnam(s1, tcp->tchktyp), f);
   __wrap_putc('(', f);

   dmp_tchk_selector(f, tcp->startedge, tcp->startxp, tcp->startcondx);
   if (tcp->tchktyp != TCHK_PERIOD && tcp->tchktyp != TCHK_WIDTH)
    {
     __wrap_puts(", ", f);
     dmp_tchk_selector(f, tcp->chkedge, tcp->chkxp, tcp->chkcondx);
    }

   __wrap_puts(", ", f);
   dmp_delay(f, tcp->tclim_du, tcp->tc_delrep, "");
   if (tcp->tc_haslim2)
    {
     __wrap_puts(", ", f);
     dmp_delay(f, tcp->tclim2_du, tcp->tc_delrep2, "");
    }

   if (tcp->ntfy_np != NULL)
    {
     __wrap_puts(", ", f);
     __wrap_puts(tcp->ntfy_np->nsym->synam, f);
    }
   __nl_wrap_puts(");", f);
  }
}
