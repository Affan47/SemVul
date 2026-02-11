algoritmo(gint num_jug)
{
	gint x,y,i;

	char barcos[11];

	for(i=0;i<11;i++)
		barcos[i]=0;

	x=0;y=0;


	if(!(algoritmo_rec(&x,&y,num_jug,barcos) ))
		return FALSE;

	if(	(barcos[1]==4) &&
		(barcos[2]==3) &&
		(barcos[3]==2) &&
		(barcos[4]==1) &&
		(barcos[5]==0) &&
		(barcos[6]==0) &&
		(barcos[7]==0) &&
		(barcos[8]==0) &&
		(barcos[9]==0) &&
		(barcos[10]==0)
	)
		return TRUE;
	else
		return FALSE;
}
