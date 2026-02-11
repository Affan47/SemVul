BSphere(void) const
{

    switch(radii.Sextant()) {
    case RN_NX_SEXTANT: return R3Sphere(Center(), radii.X());
    case RN_PX_SEXTANT: return R3Sphere(Center(), radii.X());
    case RN_NY_SEXTANT: return R3Sphere(Center(), radii.Y());
    case RN_PY_SEXTANT: return R3Sphere(Center(), radii.Y());
    case RN_NZ_SEXTANT: return R3Sphere(Center(), radii.Z());
    case RN_PZ_SEXTANT: return R3Sphere(Center(), radii.Z());
    default:
	RNAbort("Illegal sextant found");
	return R3null_sphere;
    }
}
