Include(const FMVector3& point)
{
	if (radius >= 0.0f)
	{
		float distanceSquared = (center - point).LengthSquared();
		if (distanceSquared > (radius * radius))
		{
			radius = sqrtf(distanceSquared);
		}
	}
	else
	{
		center = point;
		radius = 0.0f;
	}
}
