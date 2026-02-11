handle_option(char opt, char *optarg)
{
     FILE *wf;
     struct size sz;
     int rank, n;

     switch (opt) {
	 case 's':
	      sz = parse_size(optarg);
	      if (!sz.is_nd)
		   test_speed(sz.narray[0]);
	      else
		   test_speed_nd(sz);
	      break;

	 case 'c':
	      sz = parse_size(optarg);
	      if (!sz.is_nd)
		   test_correctness(sz.narray[0]);
	      else
		   testnd_correctness_aux(sz);
	      break;

	 case 'p':
	      rank = atoi(optarg);
	      test_planner(rank);
	      break;

	 case 'P':
	      paranoid = 1;
	      enter_paranoid_mode();
	      break;

	 case 'r':
	      rank = atoi(optarg);
	      test_all_random(rank);
	      break;

	 case 'a':
	      rank = atoi(optarg);
	      if (rank == 0)
		   test_all();
	      else
		   testnd_all(rank);
	      break;

	 case 't':
	      test_timer();
	      break;

	 case 'f':
	      n = atoi(optarg);
	      CHECK(n > 0, "-f requires a positive integer argument");
	      howmany_fields = n;
	      break;

	 case 'm':
	      measure_flag = FFTW_MEASURE;
	      break;

	 case 'e':
	      speed_flag = FFTW_ESTIMATE;
	      break;

	 case 'N':
	      no_vector_flag = FFTW_NO_VECTOR_RECURSE;
	      break;

	 case 'w':
	      wisdom_flag = FFTW_USE_WISDOM;
	      strcpy(wfname, optarg);
	      wf = fopen(wfname, "r");
	      if (wf == 0) {
		   my_printf("Couldn't open wisdom file \"%s\".\n", wfname);
		   my_printf("This file will be created upon completion.\n");
	      } else {
		   CHECK(FFTW_SUCCESS == fftw_import_wisdom_from_file(wf),
			 "invalid wisdom file format");
		   fclose(wf);
	      }
	      break;

	 case '1':
	      only_one_speed_test = 1;
	      break;

	 case 'v':
	      verbose++;
	      break;

	 case 'V':
	      my_printf("%s\n", fftw_version);
	      my_printf("%s test program, compiled in %s precision.\n",
			fftw_prefix,
			sizeof(fftw_real) == sizeof(double) ? "double"
			: (sizeof(fftw_real) == sizeof(float) ? "single"
			   : "unknown"));
	      my_printf(
  "\nCopyright (C) Massachusetts Institute of Technology.\n"
  "FFTW comes with ABSOLUTELY NO WARRANTY.  This is free software, and\n"
  "you are welcome to redistribute it under the terms of the GNU\n"
  "General Public License.  For more information, see the file COPYING or\n"
  "the GNU web site at http://www.gnu.org.\n"
  "\nFor more information regarding FFTW, or to download the latest version,\n"
  "see the FFTW home page at http://www.fftw.org.\n");

	      break;

	 case 'x':
	      n = atoi(optarg);
	      CHECK(n > 0, "-x requires a positive integer argument");
	      max_iterations = n;
	      break;

	 case 'h':
	      usage(FALSE);
	      break;

	 default:
	      usage(TRUE);
     }


     if (!(wisdom_flag & FFTW_USE_WISDOM) && chk_mem_leak)
	  fftw_check_memory_leaks();
}
