v_quat64_valid(const VNQuat64 *q)
{
	if(q == NULL)
		return 0;
	return quat_valid(q->x) && quat_valid(q->y) && quat_valid(q->z) && quat_valid(q->w);
}
