get_server_finished(SSL *s)
	{
	unsigned char *buf;
	unsigned char *p;
	int i, n, len;

	buf=(unsigned char *)s->init_buf->data;
	p=buf;
	if (s->state == SSL2_ST_GET_SERVER_FINISHED_A)
		{
		i=ssl2_read(s,(char *)&(buf[s->init_num]),1-s->init_num);
		if (i < (1-s->init_num))
			return(ssl2_part_read(s,SSL_F_GET_SERVER_FINISHED,i));
		s->init_num += i;

		if (*p == SSL2_MT_REQUEST_CERTIFICATE)
			{
			s->state=SSL2_ST_SEND_CLIENT_CERTIFICATE_A;
			return(1);
			}
		else if (*p != SSL2_MT_SERVER_FINISHED)
			{
			if (p[0] != SSL2_MT_ERROR)
				{
				ssl2_return_error(s,SSL2_PE_UNDEFINED_ERROR);
				SSLerr(SSL_F_GET_SERVER_FINISHED,SSL_R_READ_WRONG_PACKET_TYPE);
				}
			else
				{
				SSLerr(SSL_F_GET_SERVER_FINISHED,SSL_R_PEER_ERROR);

				i=ssl2_read(s,(char *)&(p[s->init_num]),3-s->init_num);
				return ssl2_part_read(s,SSL_F_GET_SERVER_VERIFY,i);
				}
			return(-1);
			}
		s->state=SSL2_ST_GET_SERVER_FINISHED_B;
		}

	len = 1 + SSL2_SSL_SESSION_ID_LENGTH;
	n = len - s->init_num;
	i = ssl2_read(s,(char *)&(buf[s->init_num]), n);
	if (i < n)
		return(ssl2_part_read(s,SSL_F_GET_SERVER_FINISHED,i));
	s->init_num += i;
	if (s->msg_callback)
		s->msg_callback(0, s->version, 0, buf, (size_t)s->init_num, s, s->msg_callback_arg);

	if (!s->hit)
		{


		s->session->session_id_length=SSL2_SSL_SESSION_ID_LENGTH;
		memcpy(s->session->session_id,p+1,SSL2_SSL_SESSION_ID_LENGTH);
		}
	else
		{
		if (!(s->options & SSL_OP_MICROSOFT_SESS_ID_BUG))
			{
			if ((s->session->session_id_length > sizeof s->session->session_id)
			    || (0 != memcmp(buf + 1, s->session->session_id,
			                    (unsigned int)s->session->session_id_length)))
				{
				ssl2_return_error(s,SSL2_PE_UNDEFINED_ERROR);
				SSLerr(SSL_F_GET_SERVER_FINISHED,SSL_R_SSL_SESSION_ID_IS_DIFFERENT);
				return(-1);
				}
			}
		}
	s->state = SSL_ST_OK;
	return(1);
	}
