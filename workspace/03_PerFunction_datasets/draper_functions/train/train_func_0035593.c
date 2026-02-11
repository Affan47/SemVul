addPowerUps(int o, int duration, int a, int b, int c)
{

	int		i;
#if 0
	int		pwrPause00 = 1;
	int		pwrPause01 = 1;
	int		pwrPause02 = 1;
#else
	int		pwrPause00 = a+(int)(FRAND*500);
	int		pwrPause01 = b+(int)(FRAND*500);
	int		pwrPause02 = c+(int)(FRAND*1500);
#endif
	float	p[3] = {0.0, 9.0, 25.0};

	for(i = o; i < o+duration; i++)
	{
		pwrPause00--;
		pwrPause01--;
		pwrPause02--;
		p[0] = 8.0*SRAND;
		if(pwrPause00 < 1)
		{
			pwrPause00 = 2500+(int)(SRAND*700);
			addItem(i, new PowerUp(PowerUps::Shields, p) );
		}
		else if(pwrPause01 < 1)
		{
			pwrPause01 = 4000+(int)(SRAND*900);
			addItem(i, new PowerUp(PowerUps::Repair, p) );
		}
		else if(pwrPause02 < 1)
		{
			pwrPause02 = 5000+(int)(SRAND*3000);

			addItem(i, new PowerUp(PowerUps::SuperShields, p) );
		}
	}
}
