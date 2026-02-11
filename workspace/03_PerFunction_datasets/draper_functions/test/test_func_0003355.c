check_return(int ret)
{
	switch(ret)
	{
		case ECPG_INFORMIX_ENOTDMY:
			printf("(ECPG_INFORMIX_ENOTDMY)");
			break;
		case ECPG_INFORMIX_ENOSHORTDATE:
			printf("(ECPG_INFORMIX_ENOSHORTDATE)");
			break;
		case ECPG_INFORMIX_BAD_DAY:
			printf("(ECPG_INFORMIX_BAD_DAY)");
			break;
		case ECPG_INFORMIX_BAD_MONTH:
			printf("(ECPG_INFORMIX_BAD_MONTH)");
			break;
		default:
			printf("(unknown ret: %d)", ret);
			break;
	}
	printf("\n");
}
