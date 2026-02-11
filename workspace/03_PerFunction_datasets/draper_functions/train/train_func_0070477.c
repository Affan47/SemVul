icx_XYZ_to_cam(
struct _icxcam *s,
double Jab[3],
double XYZ[3]
) {
	switch(s->tag) {
		case cam_CIECAM97s3: {
			cam97s3 *pp = (cam97s3 *)s->p;
			return pp->XYZ_to_cam(pp, Jab, XYZ);
		}
		case cam_CIECAM02: {
			cam02 *pp = (cam02 *)s->p;
			return pp->XYZ_to_cam(pp, Jab, XYZ);
		}
		default:
			break;
	}
	return 0;
}
