analyze(DB* stat_db, DBT* block_dbt, db_recno_t dup_count, DB* ldb, DB* primary){
	DBT lkey, lval;
	DBT first_pkey, second_pkey;
	DBT rec1, rec2;
    DBT sd_dbt, sk_dbt;
	DBC* lcur, *pcur1, *pcur2;
    stat_data sd;
    void *old1, *old2;
	double match_n, nonmatch_n;
	u_int32_t match_d, nonmatch_d, all;

	match_n = nonmatch_n = match_d = nonmatch_d = 0;

	DBT_CLEAR(lkey);
	DBT_CLEAR(lval);
	DBT_CLEAR(first_pkey);
	DBT_CLEAR(second_pkey);
    DBT_CLEAR(rec1);
    DBT_CLEAR(rec2);
    DBT_CLEAR(sd_dbt);
    DBT_CLEAR(sk_dbt);

	ldb->cursor(ldb, NULL, &lcur, 0);
    primary->cursor(primary, NULL, &pcur1, 0);
    primary->cursor(primary, NULL, &pcur2, 0);

	while(DB_NOTFOUND != lcur->get(lcur, &lkey, &lval, DB_NEXT)){
		first_index(NULL, &lkey, &lval, &first_pkey);
		second_index(NULL, &lkey, &lval, &second_pkey);

        old1 = first_pkey.data;
        old2 = second_pkey.data;

		pcur1->get(pcur1, &first_pkey, &rec1, DB_SET);
		pcur2->get(pcur2, &second_pkey, &rec2, DB_SET);

        if(tagcmp((DbRecord*)rec1.data, (DbRecord*)rec2.data)==0){
			match_n += *(double*)lval.data;
			++match_d;
		}
		else {
			nonmatch_n += *(double*)lval.data;
			++nonmatch_d;
		}

        free(old1);
        free(old2);
	}

    lcur->close(lcur);
    pcur1->close(pcur1);
    pcur2->close(pcur2);


    match_n += dup_count;
    match_d += dup_count;
    sd.density = (match_n+nonmatch_n)/(match_d+nonmatch_d);
    sd.precision = match_n/match_d;
    sd.recall = nonmatch_n/nonmatch_d;
    sd.match_n = match_n;
    sd.nonmatch_n = nonmatch_n;
    sd.match_d = match_d;
    sd.nonmatch_d = nonmatch_d;
    sd.Pr_M = PR_M;
    sd.Pr_T = PR_T;

    sd_dbt.data = &sd;
    sd_dbt.size = sizeof(stat_data);

    stat_db->put(stat_db, NULL, block_dbt, &sd_dbt, DB_NOOVERWRITE);


	return(0);
}
