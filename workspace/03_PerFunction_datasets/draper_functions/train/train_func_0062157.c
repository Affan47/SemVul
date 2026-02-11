check_vitals_mapped(void)
{
    subnfunc *f;
    int v;
#define VITALS 5
    short vitals[VITALS] = { DO_EXIT, DO_EXIT, CANCEL_MSG, CANCEL_MSG, CANCEL_MSG };
    int inmenus[VITALS] = { MMAIN, MHELP, MWHEREIS, MREPLACE, MGOTOLINE };

    for  (v = 0; v < VITALS; v++) {
       for (f = allfuncs; f != NULL; f = f->next) {
           if (f->scfunc == vitals[v] && f->menus & inmenus[v]) {
               const sc *s = first_sc_for(inmenus[v], f->scfunc);
               if (!s) {
                   rcfile_error(N_("Fatal error: no keys mapped for function \"%s\""),
                       f->desc);
                   fprintf(stderr, N_("Exiting.  Please use nano with the -I option if needed to adjust your nanorc settings\n"));
                   exit(1);
               }
           break;
           }
       }
    }
}
