accept_what(g2_connection_t *to_con, size_t distance)
{
	char *w_ptr = buffer_start(*to_con->recv);

	if(to_con->u.accept.flags.second_header)
		return false;

	to_con->u.accept.flags.accept_ok = true;

	while(distance)
	{
		if(str_size(ACCEPT_G2) > distance)
			break;

		if(!strncasecmp_a(w_ptr, ACCEPT_G2, str_size(ACCEPT_G2)))
		{

			logg_develd_old("found for Accept:\t\"%.*s\"\n", str_size(ACCEPT_G2), buffer_start(*to_con->recv));
			to_con->u.accept.flags.accept_g2 = true;
			return false;
		}
		else
		{


			while(distance)
			{
				w_ptr++;
				distance--;
				if(',' == *(w_ptr-1))
					break;
			}
		}
	}

	to_con->u.accept.flags.accept_g2 = false;
	return true;
}
