collectDocEqns(const vector<Tree>& docBoxes, vector<Tree>& eqBoxes)
{
	int nbdoceqn = 0;

	for (vector<Tree>::const_iterator doc=docBoxes.begin(); doc<docBoxes.end(); doc++) {
		Tree L = reverse(*doc);
		Tree expr;
		while (isList(L)) {
			if ( isDocEqn(hd(L), expr) ) {
				eqBoxes.push_back(expr);
				nbdoceqn++;
			}
			L = tl(L);
		}
	}

}
