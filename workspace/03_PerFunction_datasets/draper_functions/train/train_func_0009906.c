t3rev2char(struct adapter *adapter)
{
	char rev = 0;

	switch(adapter->params.rev) {
	case T3_REV_B:
	case T3_REV_B2:
		rev = 'b';
		break;
	case T3_REV_C:
		rev = 'c';
		break;
	}
	return rev;
}
