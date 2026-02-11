R3Contains(const R3Plane& plane1, const R3Plane& plane2)
{

    return (R3Contains(plane1.Normal(), plane2.Normal()) &&
	    RNIsEqual(plane1.D(), plane2.D()));
}
