Start_Get()
{
    DBT local_key;
    DBT local_data;

    memset(&local_key, 0, sizeof(DBT));
    memset(&local_data, 0, sizeof(DBT));

    if (isOpen && dbp)
    {


        seqrc = dbcp->c_get(dbcp, &local_key, &local_data, DB_FIRST);
	seqerr = seqrc;

	if(!seqrc) {
	  data = 0;
	  data.append((char*)local_data.data, (int)local_data.size);
	  skey = 0;
	  skey.append((char*)local_key.data, (int)local_key.size);
	}
    }
}
