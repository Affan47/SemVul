icmMeasurement_dump(
	icmBase *pp,
	icmFile *op,
	int   verb
) {
	icmMeasurement *p = (icmMeasurement *)pp;
	if (verb <= 0)
		return;

	op->gprintf(op,"Measurement:\n");
	op->gprintf(op,"  Standard Observer = %s\n", string_StandardObserver(p->observer));
	op->gprintf(op,"  XYZ for Measurement Backing = %s\n", string_XYZNumber_and_Lab(&p->backing));
	op->gprintf(op,"  Measurement Geometry = %s\n", string_MeasurementGeometry(p->geometry));
	op->gprintf(op,"  Measurement Flare = %5.1f%%\n", p->flare * 100.0);
	op->gprintf(op,"  Standard Illuminant = %s\n", string_Illuminant(p->illuminant));
}
