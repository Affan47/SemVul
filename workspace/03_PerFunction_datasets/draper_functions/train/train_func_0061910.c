test_random(void)
{
    sasl_rand_t *rpool;
    int lup;
    char buf[4096];


    for (lup = 0;lup<10;lup++)
    {
	if (sasl_randcreate(&rpool) != SASL_OK) fatal("sasl_randcreate failed");
	sasl_randfree(&rpool);
    }


    rpool = NULL;
    sasl_randseed(rpool, "seed", 4);


    sasl_randcreate(&rpool);
    sasl_randseed(rpool, "seed", 0);
    sasl_randseed(rpool, NULL, 0);
    sasl_randseed(rpool, NULL, 4);
    sasl_randfree(&rpool);


    sasl_randcreate(&rpool);
    sasl_churn(rpool, "seed", 0);
    sasl_churn(rpool, NULL, 0);
    sasl_churn(rpool, NULL, 4);
    sasl_randfree(&rpool);


    sasl_randcreate(&rpool);

    for (lup=0;lup<(int) sizeof(buf);lup++)
    {
	buf[lup] = (char) (rand() % 256);
    }
    sasl_randseed(rpool, buf, sizeof(buf));
    sasl_churn(rpool, buf, sizeof(buf));

    sasl_randfree(&rpool);
}
