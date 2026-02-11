accuimult (double a, double b, double a1, double b1)
{   if (a>=0)
	{	if (a1>=0)
		{	accuload(&h,a); accuload(&g,a1);
			accuload(&h1,b); accuload(&g1,b1);
		}
		else if (b1>=0)
		{	accuload(&h,b); accuload(&g,a1);
			accuload(&h1,b); accuload(&g1,b1);
		}
		else
		{	accuload(&h,b); accuload(&g,a1);
			accuload(&h1,a); accuload(&g1,b1);
		}
	}
	else if (b>=0)
	{	if (a1>=0)
		{	accuload(&h,a); accuload(&g,b1);
			accuload(&h1,b); accuload(&g1,b1);
		}
		else if (b1>=0)
		{   if (a*b1 <= b*a1)
			{	accuload(&h,a); accuload(&g,b1);
			}
			else
			{	accuload(&h,b); accuload(&g,a1);
			}
			if (b*b1 >= a*a1)
			{	accuload(&h1,b); accuload(&g1,b1);
			}
			else
			{	accuload(&h1,a); accuload(&g1,a1);
			}
		}		else
		{	accuload(&h,b); accuload(&g,a1);
			accuload(&h1,a); accuload(&g1,b1);
		}
	}
	else
	{	if (a1>=0)
		{	accuload(&h,a); accuload(&g,b1);
			accuload(&h1,b); accuload(&g1,a1);
		}
		else if (b1>=0)
		{	accuload(&h,a); accuload(&g,b1);
			accuload(&h1,a); accuload(&g1,a1);
		}
		else
		{	accuload(&h,b); accuload(&g,b1);
			accuload(&h1,a); accuload(&g1,a1);
		}
	}
	accumult(&g,&h); accuadd(&A1,&g); if (error) return;
	accumult(&g1,&h1); accuadd(&A2,&g1);
}
