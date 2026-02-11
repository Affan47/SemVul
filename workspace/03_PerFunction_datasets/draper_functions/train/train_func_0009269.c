nbiof_ctrl(BIO *b, int cmd, long num, void *ptr)
	{
	long ret;

	if (b->next_bio == NULL) return(0);
	switch (cmd)
		{
        case BIO_C_DO_STATE_MACHINE:
		BIO_clear_retry_flags(b);
		ret=BIO_ctrl(b->next_bio,cmd,num,ptr);
		BIO_copy_next_retry(b);
		break;
	case BIO_CTRL_DUP:
		ret=0L;
		break;
	default:
		ret=BIO_ctrl(b->next_bio,cmd,num,ptr);
		break;
		}
	return(ret);
	}
