dump_allow(FILE *file)
{
	switch (allow_overlap) {
	case ao_none:
		break;
	case ao_touch:
		fprintf(file, "allow touch\n");
		break;
	case ao_any:
		fprintf(file, "allow overlap\n");
		break;
	default:
		abort();
	}
}
