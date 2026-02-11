HPL_ptimer_boot( void )
#else
void HPL_ptimer_boot()
#endif
{


   int                        i;


   HPL_ptimer_disabled = 0;

   for( i = 0; i < HPL_NPTIMER; i++ )
   {
      HPL_ptimer_cpusec  [i] = HPL_ptimer_wallsec  [i] = HPL_rzero;
      HPL_ptimer_cpustart[i] = HPL_ptimer_wallstart[i] = HPL_PTIMER_STARTFLAG;
   }


}
