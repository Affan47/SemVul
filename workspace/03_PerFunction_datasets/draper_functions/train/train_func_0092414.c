stddev()
{
	double the_mean = mean();
	double sum = 0.0;
	long good = 0;
	for (unsigned int i = 0; i < the_depth; i++)
		if (!gr_missing(contents[i])) {
			double tmp = (contents[i] - the_mean);
			sum += tmp * tmp;
			good++;
		}
	if (good > 1)
		return double(sqrt(sum / (good - 1)));
	else
		return gr_currentmissingvalue();
}
