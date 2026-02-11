run(const BaseImage *in, const Par &par)
{
	set_implementation(implementation, par); if (!implementation) { return NULL; }
	return implementation->run(in, par);
}
