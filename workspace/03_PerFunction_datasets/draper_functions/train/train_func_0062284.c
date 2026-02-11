main(int argc, char **argv) {
	struct QueueBuffer *qb;
	char buffer[256];
	char bigbuffer[165500];
	int i, bytes;

	memset(bigbuffer, '.', sizeof(bigbuffer));


	printf("\n == Test 1 == \n\n");

	qb_initialize(&qb);

	qb_push(qb, bigbuffer, sizeof(bigbuffer));
	for (i = 0; i < 4096; i += 16)
		qb_push(qb, "Here r 16 char. ", 16);

	while ((bytes = qb_pop(qb, buffer, 32)) > 0) {
		buffer[bytes] = '\0';
		printf("%08d bytes remaining after pop : \"%s\"\n",
				qb_getSize(qb), buffer);
	}

	qb_free(&qb);


	printf("\n == Test 2 == \n\n");

	qb_initialize(&qb);
	qb_push(qb, bigbuffer, 15000);
	while ((bytes = qb_pop(qb, buffer, 256)) > 128) {
		qb_push(qb, bigbuffer, 128);
	}
	qb_free(&qb);


	printf("\n == Test 3 == \n\n");

	qb_initialize(&qb);
	qb_free(&qb);


	printf("\n == Test 4 == \n\n");

	qb_initialize(&qb);
	qb_push(qb, bigbuffer, sizeof(bigbuffer));
	qb_pop(qb, buffer, 64);
	qb_free(&qb);


	if (qb == NULL)
		printf("qb is correctly now a NULL pointer\n");
	else
		printf("qb is NOT a NULL pointer as it should be\n");


	printf("\nDone!\n\n");
	return 0;
}
