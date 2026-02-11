BuildRawFormula (map<int, int> &raw)
{
	std::map<int,int> const &m = residue->GetRawFormula ();
	map<int, int>::const_iterator j, jend = m.end();
	for (j = m.begin (); j != jend; j++){
		raw[(*j).first] += stoich * (*j).second;}
}
