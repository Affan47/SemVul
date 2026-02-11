dtIntersectSegSeg2D(const float* ap, const float* aq,
						 const float* bp, const float* bq,
						 float& s, float& t)
{
	float u[3], v[3], w[3];
	dtVsub(u,aq,ap);
	dtVsub(v,bq,bp);
	dtVsub(w,ap,bp);
	float d = vperpXZ(u,v);
	if (fabsf(d) < 1e-6f) return false;
	s = vperpXZ(v,w) / d;
	t = vperpXZ(u,w) / d;
	return true;
}
