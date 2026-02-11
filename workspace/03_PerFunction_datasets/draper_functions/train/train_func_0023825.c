IsPlanar(void) const
{

    return ((radii.X() == 0.0) || (radii.Y() == 0.0) || (radii.Z() == 0.0));
}
