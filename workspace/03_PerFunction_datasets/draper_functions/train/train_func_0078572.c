xsh_report_cpu(FILE *fp, char *str)
#endif
{
      static int call_no = 0;
      double utime, s_time;

      get_cpu_time(&utime, &s_time);

      if ( str == NULL )
	{
	  if ( call_no++ == 0 )
                fprintf(fp,"Preprocessing");
	  else
	        fprintf(fp,"Total CPU");
	}
      else
	        fprintf(fp,"%s", str);

      fprintf(fp," time:\t%2.2fu  %2.2fs\t%2.2f (sec)\n", utime, s_time,
	                                                   utime + s_time);


}
