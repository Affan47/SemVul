mapEvalDocEqn(const vector<Tree>& eqBoxes, const Tree& env, vector<Tree>& evalEqBoxes)
{


	for ( vector<Tree>::const_iterator eq=eqBoxes.begin(); eq < eqBoxes.end(); eq++)
	{
		evalEqBoxes.push_back(evaldocexpr( *eq, env ));
	}

}
