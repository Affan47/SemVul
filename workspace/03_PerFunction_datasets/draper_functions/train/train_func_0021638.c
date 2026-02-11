step(vector<double> &value,  double step, RNG *rng) const
{

    for (unsigned int i = 0; i < value.size(); ++i) {
	value[i] *= exp(step * rng->normal());
    }
}
