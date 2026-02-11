MGD77_Correction_Rec (struct MGD77_CORRECTION *C, double *value, double *aux)
{

	double dz = 0.0, z;
	struct MGD77_CORRECTION *current = NULL;

	for (current = C; current; current = current->next) {
		if (current->id == -1) {
			dz = current->factor;
		}
		else {
			z = (current->id >= MGD77_MAX_COLS) ? aux[current->id-MGD77_MAX_COLS] : value[current->id];
			if (current->power == 1.0)
				dz += current->factor * ((current->modifier) (current->scale * (z - current->origin)));
			else
				dz += current->factor * pow ((current->modifier) (current->scale * (z - current->origin)), current->power);
		}
	}
	return (dz);
}
