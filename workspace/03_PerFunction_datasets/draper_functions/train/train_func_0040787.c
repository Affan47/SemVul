get_certificate_status(const char *serial, CA_DB *db)
	{
	char *row[DB_NUMBER],**rrow;
	int ok=-1,i;


	for (i=0; i<DB_NUMBER; i++)
		row[i]=NULL;


	row[DB_serial] = OPENSSL_malloc(strlen(serial) + 2);
	if (row[DB_serial] == NULL)
		{
		BIO_printf(bio_err,"Malloc failure\n");
		goto err;
		}

	if (strlen(serial) % 2)
		{
		;
		row[DB_serial][0]='0';


		memcpy(row[DB_serial]+1, serial, strlen(serial));
		row[DB_serial][strlen(serial)+1]='\0';
		}
	else
		{

		memcpy(row[DB_serial], serial, strlen(serial));
		row[DB_serial][strlen(serial)]='\0';
		}


	for (i=0; row[DB_serial][i] != '\0'; i++)
		row[DB_serial][i] = toupper((unsigned char)row[DB_serial][i]);


	ok=1;


	rrow=TXT_DB_get_by_index(db->db,DB_serial,row);
	if (rrow == NULL)
		{
		BIO_printf(bio_err,"Serial %s not present in db.\n",
				 row[DB_serial]);
		ok=-1;
		goto err;
		}
	else if (rrow[DB_type][0]=='V')
		{
		BIO_printf(bio_err,"%s=Valid (%c)\n",
			row[DB_serial], rrow[DB_type][0]);
		goto err;
		}
	else if (rrow[DB_type][0]=='R')
		{
		BIO_printf(bio_err,"%s=Revoked (%c)\n",
			row[DB_serial], rrow[DB_type][0]);
		goto err;
		}
	else if (rrow[DB_type][0]=='E')
		{
		BIO_printf(bio_err,"%s=Expired (%c)\n",
			row[DB_serial], rrow[DB_type][0]);
		goto err;
		}
	else if (rrow[DB_type][0]=='S')
		{
		BIO_printf(bio_err,"%s=Suspended (%c)\n",
			row[DB_serial], rrow[DB_type][0]);
		goto err;
		}
	else
		{
		BIO_printf(bio_err,"%s=Unknown (%c).\n",
			row[DB_serial], rrow[DB_type][0]);
		ok=-1;
		}
err:
	for (i=0; i<DB_NUMBER; i++)
		{
		if (row[i] != NULL)
			OPENSSL_free(row[i]);
		}
	return(ok);
	}
