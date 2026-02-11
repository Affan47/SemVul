wrwisdom(void)
{
     FILE *f;
     double tim;
     if (!havewisdom) return;

     timer_start(USER_TIMER);
     if ((f = fopen(wisdat, "w"))) {
	  export_wisdom(f);
	  fclose(f);
     }
     tim = timer_stop(USER_TIMER);
     if (verbose > 1) printf("write wisdom took %g seconds\n", tim);
}
