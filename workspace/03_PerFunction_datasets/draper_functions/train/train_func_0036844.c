mapCompileDocEqnSigs(const vector<Tree>& eqSigs, const vector<int>& eqInputs, const vector<int>& eqOutputs, DocCompiler* DC, vector<Lateq*>& docCompiledEqnsVector)
{


	for( unsigned int i=0; i < eqSigs.size(); i++ ) {


		docCompiledEqnsVector.push_back( DC->compileLateq(eqSigs[i], new Lateq(eqInputs[i], eqOutputs[i])) );
	}


}
