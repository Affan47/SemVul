g3d_quat_normalize(G3DQuat *q)
{
	gint32 i;
	G3DDouble div = 0;

	for(i = 0; i < 4; i ++)
		div += (q[i] * q[i]);
	for(i = 0; i < 4; i ++)
		q[i] /= div;

	return TRUE;
}
