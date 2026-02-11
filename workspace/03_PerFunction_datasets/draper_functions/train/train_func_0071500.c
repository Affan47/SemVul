readPt(istream &in, ANNpoint p)
{
	for (int i = 0; i < dim; i++) {
		if(!(in >> p[i])) return false;
	}
	return true;
}
