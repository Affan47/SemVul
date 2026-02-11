check_remesh(Sphere *sphere, const Appearance *ap)
{
  if (sphere->geomflags & SPHERE_REMESH) {
    return true;
  }
  if (ap->valid & APF_DICE) {
    if (sphere->ntheta == ap->dice[0] &&
	sphere->nphi == ap->dice[1]) {
      return false;
    }
    sphere->ntheta = ap->dice[0];
    sphere->nphi = ap->dice[1];
    sphere->geomflags |= SPHERE_REMESH;
    return true;
  }
  return false;
}
