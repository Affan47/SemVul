HideBackbone_ (MolComplexS *mol_complexSP, int mol_complexesN)
{
int		mol_complexI;
MolComplexS	*curr_mol_complexSP;
size_t		c_alphaI, c_alphaN;
BackboneS	*curr_backboneSP;
AtomS		*curr_atomSP;


for (mol_complexI = 0; mol_complexI < mol_complexesN; mol_complexI++)
	{

	curr_mol_complexSP = mol_complexSP + mol_complexI;


	if (curr_mol_complexSP->catchF == 0) continue;


	c_alphaN = curr_mol_complexSP->c_alphaN;


	for (c_alphaI = 0; c_alphaI < c_alphaN; c_alphaI++)
		{

		curr_backboneSP = curr_mol_complexSP->backboneSP + c_alphaI;
		curr_atomSP = curr_mol_complexSP->atomSP +
			      curr_backboneSP->c_alphaI;


		if (curr_atomSP->selectedF) curr_backboneSP->hiddenF = 1;
		}
	}


return 1;
}
