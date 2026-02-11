sort_duration(unsigned int chord[MAX_CHORD][5], int l, int r)
{
	int i, j;
	unsigned int temp[5];

	for(i=l; i<r; i++) {
		int min=i;
		for(j=i+1; j<=r; j++)
			if((chord[j][2]+chord[j][4])<(chord[min][2]+chord[j][4]))
				min=j;
		temp[0]=chord[i][0];
		temp[1]=chord[i][1];
		temp[2]=chord[i][2];
		temp[3]=chord[i][3];
		temp[4]=chord[i][4];
		chord[i][0]=chord[min][0];
		chord[i][1]=chord[min][1];
		chord[i][2]=chord[min][2];
		chord[i][3]=chord[min][3];
		chord[i][4]=chord[min][4];
		chord[min][0]=temp[0];
		chord[min][1]=temp[1];
		chord[min][2]=temp[2];
		chord[min][3]=temp[3];
		chord[min][4]=temp[4];
	}
}
