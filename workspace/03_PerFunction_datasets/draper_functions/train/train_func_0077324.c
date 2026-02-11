ExtractHNCAC_ (VectorS  *H_vectorSP, VectorS *N_vectorSP,
		   VectorS *CA_vectorSP, VectorS *C_vectorSP,
		   AtomS *atomSP, size_t atom_startI, size_t atom_endI)
{
int		vectors_extractedN = 0;
size_t		atomI;
AtomS		*curr_atomSP;
int		H_foundF = 0, N_foundF = 0, CA_foundF = 0, C_foundF = 0;


for (atomI = atom_startI; atomI <= atom_endI; atomI++)
	{

	curr_atomSP = atomSP + atomI;


	if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "H") == 0)
		{
		if (H_foundF) continue;
                H_vectorSP->x = curr_atomSP->raw_atomS.x[0];
                H_vectorSP->y = curr_atomSP->raw_atomS.y;
                H_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		H_foundF = 1;
		}


	if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "N") == 0)
		{
		if (N_foundF) continue;
		N_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		N_vectorSP->y = curr_atomSP->raw_atomS.y;
		N_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		N_foundF = 1;
		}


	else if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "CA") == 0)
		{
		if (CA_foundF) continue;
		CA_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		CA_vectorSP->y = curr_atomSP->raw_atomS.y;
		CA_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		CA_foundF = 1;
		}


	else if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "C") == 0)
		{
		if (C_foundF) continue;
		C_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		C_vectorSP->y = curr_atomSP->raw_atomS.y;
		C_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		C_foundF = 1;
		}
	}


return vectors_extractedN;
}
