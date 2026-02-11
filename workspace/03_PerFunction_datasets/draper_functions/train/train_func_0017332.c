check_whitelist(char *conf, request_rec *r)
{
	unsigned long first;
	unsigned long last;
	unsigned long mask;
	char ippi[16];
	struct in_addr in;


	stat(conf,&statdata);
	access_time = localtime(&statdata.st_mtime);
	snprintf(timestamp,9,"%d:%d:%d",access_time->tm_hour,access_time->tm_min,access_time->tm_sec);

	if (strcmp(old_timestamp,timestamp) != 0)
	{
		ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, "Reloading whitelist");
		strncpy(old_timestamp,timestamp,9);
		update_whitelist(conf);
	}


	int count = 0;

	for (count; count < WHITELIST_SIZE; count++)
	{

		if (lista[count][0] == '\0') return 0;

		brokenfeed = strchr(lista[count], '\n');
		if ( brokenfeed ) *brokenfeed =  '\0';

		if ( (strchr(lista[count],'/') == NULL )){
			if ( strcmp(lista[count],CLIENT_IP(r->connection)) == 0  ) return 1;
		}
		else {

			sscanf(lista[count], "%[^/]/%u", ippi, &bitmask);
			sscanf(ippi, "%lu.%lu.%lu.%lu", &a, &b, &c, &d);

			first = (a << 24) + (b << 16) + (c << 8) + d;

			mask = (0xFFFFFFFF << (32 - bitmask));

			last = first + (~mask);
			first = htonl(first);
			last = htonl(last);

			in.s_addr = first;

			sscanf(inet_ntoa(in), "%d.%d.%d.%d", &a_min, &b_min, &c_min, &d_min);

			in.s_addr = last;

			sscanf(inet_ntoa(in), "%d.%d.%d.%d", &a_max, &b_max, &c_max, &d_max);
			sscanf(CLIENT_IP(r->connection), "%d.%d.%d.%d", &a_daverificare, &b_daverificare, &c_daverificare, &d_daverificare);

			if (

					((d_daverificare <=  d_max) && (d_daverificare >=  d_min)) &&
					((c_daverificare <=  c_max) && (c_daverificare >=  c_min)) &&
					((b_daverificare <=  b_max) && (b_daverificare >=  b_min)) &&
					((a_daverificare <=  a_max) && (a_daverificare >=  a_min))

			   ) return 1;


		}

	}

	return 0;
}
