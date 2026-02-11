mean()
{
	double sum = 0.0;
	long good = 0;
	for (unsigned int i = 0; i < the_depth; i++)
		if (!gr_missing(contents[i])) {
			sum += contents[i];
			good++;
		}
	if (good)
		return double(sum / good);
	else
		return gr_currentmissingvalue();
}
