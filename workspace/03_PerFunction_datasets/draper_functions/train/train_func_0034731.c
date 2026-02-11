CNStoBIG5(unsigned short cns, unsigned char lc)
{
	int			i;
	unsigned int big5 = 0;

	cns &= 0x7f7f;

	switch (lc)
	{
		case LC_CNS11643_1:
			big5 = BinarySearchRange(cnsPlane1ToBig5Level1, 24, cns);
			break;
		case LC_CNS11643_2:
			big5 = BinarySearchRange(cnsPlane2ToBig5Level2, 47, cns);
			break;
		case LC_CNS11643_3:
			for (i = 0; i < sizeof(b2c3) / (sizeof(unsigned short) * 2); i++)
			{
				if (b2c3[i][1] == cns)
					return (b2c3[i][0]);
			}
			break;
		case LC_CNS11643_4:
			for (i = 0; i < sizeof(b1c4) / (sizeof(unsigned short) * 2); i++)
			{
				if (b1c4[i][1] == cns)
					return (b1c4[i][0]);
			}
		default:
			break;
	}
	return big5;
}
