gluProject2(float objx, float objy, float objz, const float model[16], const float proj[16], const int viewport[4], float *winx, float *winy)
{

	float in[4], out[4], temp;


	in[0] = objx;
	in[1] = objy;
	in[2] = objz;
	in[3] = 1.0;
	transform_point(out, model, in);
	transform_point(in, proj, out);


	if (in[3] == 0.0)
		return false;

	temp = 1.0 / in[3];
	in[0] *= temp;
	in[1] *= temp;
	in[2] *= temp;


	*winx = viewport[0] + (1 + in[0]) * (float) viewport[2] * 0.5;
	*winy = viewport[1] + (1 + in[1]) * (float) viewport[3] * 0.5;
	return true;
}
