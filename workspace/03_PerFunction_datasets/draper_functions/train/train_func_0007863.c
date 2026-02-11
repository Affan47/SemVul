fmin(float f1, float f2, float f3)
	{
		if ((f1<=f2) && (f1<=f3))
			return f1;
		else if (f2<=f3)
			return f2;
		else
			return f3;
	}
