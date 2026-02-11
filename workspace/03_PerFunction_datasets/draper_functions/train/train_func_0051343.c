set_vector_plane(Plane *plane)
{
	gint i;
	gint j;
	gdouble n;

	n = 0.0;
	for(i=0;i<3;i++)
		n += plane->Vector.C[i]*plane->Vector.C[i];
	n = sqrt(n);
	for(i=0;i<3;i++)
		plane->Vector.C[i] /= n;
	j = 0;
	for(i=1;i<3;i++)
		if(plane->Vector.C[i]>plane->Vector.C[j])
			j = i;

	plane->V[0].C[j] = 0.0;
	plane->V[0].C[(j+1)%3] = 1;
	plane->V[0].C[(j+2)%3] = 1;

	n = 0.0;
	for(i=0;i<3;i++)
	n += 	plane->Vector.C[i]*plane->V[0].C[i];

	if(plane->Vector.C[j] != 0)
	plane->V[0].C[j] = -n/plane->Vector.C[j];
	else
	{
		for(i=0;i<3;i++)
			plane->V[0].C[i] = 1;
		plane->V[0].C[(j+1)%3] = 1.0;
	}


	n = 0.0;
	for(i=0;i<3;i++)
		n += plane->V[0].C[i]*plane->V[0].C[i];
	n = sqrt(n);
	for(i=0;i<3;i++)
		plane->V[0].C[i] /= n;
	for(i=0;i<3;i++)
		plane->V[1].C[i] = plane->Vector.C[(i+1)%3]*plane->V[0].C[(i+2)%3]- plane->Vector.C[(i+2)%3]*plane->V[0].C[(i+1)%3];
}
