RS_SetTexcoords (rs_stage_t *stage, float *os, float *ot, msurface_t *fa)
{
	RS_ScaleTexcoords(stage, os, ot);


	if (stage->rot_speed)
		RS_RotateST (os, ot, -stage->rot_speed * rs_realtime * 0.0087266388888888888888888888888889, fa);

}
