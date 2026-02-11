Include(const FMVector3& point)
{
	if (point.x < minimum.x) minimum.x = point.x;
	else if (point.x > maximum.x) maximum.x = point.x;
	if (point.y < minimum.y) minimum.y = point.y;
	else if (point.y > maximum.y) maximum.y = point.y;
	if (point.z < minimum.z) minimum.z = point.z;
	else if (point.z > maximum.z) maximum.z = point.z;
}
