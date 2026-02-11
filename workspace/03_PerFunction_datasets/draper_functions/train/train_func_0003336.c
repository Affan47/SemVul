setTargetVelocity (double const (&velocity)[3])
{
	for (int i = 0; i < 3; i++) {
		target_.velocity[i] = velocity[i];
	}
}
