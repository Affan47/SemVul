ExtractH_ (VectorS *H_vectorSP,
	       AtomS *atomSP, size_t atom_startI, size_t atom_endI)
{
int		vectors_extractedN = 0;
size_t		atomI;
AtomS		*curr_atomSP;


for (atomI = atom_startI; atomI <= atom_endI; atomI++)
	{

	curr_atomSP = atomSP + atomI;


	if (strcmp (curr_atomSP->raw_atomS.pure_atom_nameA, "H") == 0)
		{
		H_vectorSP->x = curr_atomSP->raw_atomS.x[0];
		H_vectorSP->y = curr_atomSP->raw_atomS.y;
		H_vectorSP->z = curr_atomSP->raw_atomS.z[0];
		vectors_extractedN++;
		break;
		}
	}


return vectors_extractedN;
}
