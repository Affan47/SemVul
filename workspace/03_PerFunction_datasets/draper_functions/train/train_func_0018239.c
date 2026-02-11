marchingcubeinit(int stype)
{
	int i,j,k;

	if(stype==1)
	{
		for(i=0;i<plength;i++)
		{
			for(j=0;j<pwidth;j++)
			{
				for(k=0;k<pheight;k++)
				{
					vp[i][j][k].isbound=false;
				}
			}
		}

	}

	else if(stype==4)
	{

		for(i=0;i<plength;i++)
		{
			for(j=0;j<pwidth;j++)
			{
				for(k=0;k<pheight;k++)
				{
					vp[i][j][k].isdone=false;
					if(vp[i][j][k].isbound)
					{
						vp[i][j][k].isdone=true;
					}

					vp[i][j][k].isbound=false;
				}
			}
		}

	}
	else if(stype==2)
	{

		for(i=0;i<plength;i++)
		{
			for(j=0;j<pwidth;j++)
			{
				for(k=0;k<pheight;k++)
				{

					if(vp[i][j][k].isbound && vp[i][j][k].isdone)
					{
						vp[i][j][k].isbound=false;
					}
					else if(vp[i][j][k].isbound && !vp[i][j][k].isdone)
					{
						vp[i][j][k].isdone=true;
					}
				}
			}
		}

	}

	else if(stype==3)
	{
		for(i=0;i<plength;i++)
		{
			for(j=0;j<pwidth;j++)
			{
				for(k=0;k<pheight;k++)
				{
					vp[i][j][k].isbound=false;
				}
			}
		}
	}

}
