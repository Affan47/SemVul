zDumpTrellis(zTrellis* trellis, coor_t start, coor_t end) {
	coor_t pos;
	int    state;
	int i = 0;

	printf("dump score in (%u, %u)\n", start, end);

	for (pos = start; pos<= end; pos++) {
		printf("pos %u\n", pos);
		if(i == 10){ i = 0;}
		if(i==0) {
			printf("\n");

			for (state = 0; state < trellis->hmm->states; state++) {
				printf("%10s\t", zStrIdx2Char(trellis->hmm->state[state].name) );
			}
			printf("\n");
		}

		i ++;
		for (state = 0; state < trellis->hmm->states; state++) {
			printf("%10g\t", trellis->cell[state][pos].score[0]);
		}
		printf("\n");
	}

}
