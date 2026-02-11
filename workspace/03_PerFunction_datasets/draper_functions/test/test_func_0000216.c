MostDeepPoints(
					LineContactSet & points,
					const dVector3 plane_normal,
					dReal plane_dist,
					LineContactSet & deep_points)
{
	int i;
	int max_candidates[8];
	dReal maxdeep=-dInfinity;
	dReal dist;

	deep_points.Count = 0;
	for(i=0;i<points.Count;i++)
	{
		dist = DOT(plane_normal,points.Points[i]) - plane_dist;
		dist *= -1.0f;
		if(dist>maxdeep)
		{
			maxdeep = dist;
			deep_points.Count=1;
			max_candidates[deep_points.Count-1] = i;
		}
		else if(dist+REAL(0.000001)>=maxdeep)
		{
			deep_points.Count++;
			max_candidates[deep_points.Count-1] = i;
		}
	}

	for(i=0;i<deep_points.Count;i++)
	{
		SET(deep_points.Points[i],points.Points[max_candidates[i]]);
	}
	return maxdeep;

}
