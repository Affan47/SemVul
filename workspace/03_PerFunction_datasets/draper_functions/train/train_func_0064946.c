ExtractCACB_ (VectorS  *CA_vectorSP, VectorS *CB_vectorSP,
		  AtomS *atomSP, size_t atom_startI, size_t atom_endI)
{
int		vectors_extractedN = 0;
size_t		atomI;
AtomS		*curr_atomSP;
int		CA_foundF = 0, CB_foundF = 0;


for (atomI = atom_startI; atomI <= atom_endI; atomI++)
	{

	curr_atomSP = atomSP + atomI;


	if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "CA") == 0)
		{
		if (CA_foundF) continue;
		CA_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		CA_vectorSP->y = curr_atomSP->raw_atomS.y;
		CA_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		CA_foundF = 1;
		}


	else if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "CB") == 0)
		{
		if (CB_foundF) continue;
		CB_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		CB_vectorSP->y = curr_atomSP->raw_atomS.y;
		CB_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		CB_foundF = 1;
		}
	}


return vectors_extractedN;
}
