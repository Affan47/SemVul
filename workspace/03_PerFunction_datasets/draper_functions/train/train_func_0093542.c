ReadTemplateFile_ (RuntimeS *runtimeSP,
		       FILE *template_fileP, ConfigS *configSP)
{
size_t		rgb_struct_size;
int		line_size;
char		lineA[STRINGSIZE];
int		first_char;
int		rec_typeI = 0;
int		template_atomI = 0;
AtomS		*curr_atomSP;
int		surfaceI;


rgb_struct_size = sizeof (RGBS);


line_size = sizeof (lineA);


while (fgets (lineA, line_size, template_fileP))
	{


	first_char = *lineA;


	rec_typeI = 0;
	switch (first_char)
		{
		case 'A':
			if (strstr (lineA, "ATOM") == lineA) rec_typeI = 1;
			break;
		case 'H':
			if (strstr (lineA, "HETATM") == lineA) rec_typeI = 2;
			break;
		default:
			;
		}


	if (rec_typeI == 0) continue;


	curr_atomSP = runtimeSP->template_atomSP + template_atomI;


	if (ParsePDBAtomicData_ (curr_atomSP, lineA) < 0) continue;


	curr_atomSP->raw_atomS.atom_styleI = configSP->default_atom_styleI;


	curr_atomSP->raw_atomS.model_serialI = 0;


	curr_atomSP->selectedF = 1;


	curr_atomSP->hiddenF = 0;


	curr_atomSP->inside_slabF = 1;


	curr_atomSP->labelF = 0;


	if (rec_typeI == 1) curr_atomSP->raw_atomS.heteroF = 0;
	else curr_atomSP->raw_atomS.heteroF = 1;


	curr_atomSP->surfacesN = configSP->default_surfacesN;


	for (surfaceI = 0; surfaceI < MAXCOLORSURFACES; surfaceI++)
		{
		memcpy (curr_atomSP->left_rgbSA + surfaceI,
			configSP->left_rgbSA + surfaceI,
			rgb_struct_size);
		memcpy (curr_atomSP->middle_rgbSA + surfaceI,
			configSP->middle_rgbSA + surfaceI,
			rgb_struct_size);
		memcpy (curr_atomSP->right_rgbSA + surfaceI,
			configSP->right_rgbSA + surfaceI,
			rgb_struct_size);
		}


	template_atomI++;


	if (template_atomI >= MAXTEMPLATEATOMS) break;
	}


runtimeSP->template_atomsN = template_atomI;


if (ExtractTemplateResidues_ (runtimeSP) < 0)
	{
	runtimeSP->template_atomsN = 0;
	if (runtimeSP->template_atomSP)
		{
		free (runtimeSP->template_atomSP);
		runtimeSP->template_atomSP = NULL;
		}
	return 0;
	}


return template_atomI;
}
