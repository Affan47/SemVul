preprocess(int flag,CUSINK * cu, int cunum){
FILE * ifp ;
double sink_delay ;

		if ( flag == 1)
			system("./cu1.pl -s -v1 infile outfile tuned_45nm_HP.pm > cutest");
		else if(flag == 0)
			system("./cu0.pl -s -v1 infile outfile  tuned_45nm_HP.pm > cutest");
		else{
			printf(" error flag for inverter ? \n");
			return 0;
		}


		ifp = (FILE *) fopen("cutest","r");
		if ( ifp == NULL){
			printf("no test file generated\n");
			return -1;
		}

		cal_sink_d(ifp,cu);
		fclose(ifp);


	return (int)sink_delay;

}
