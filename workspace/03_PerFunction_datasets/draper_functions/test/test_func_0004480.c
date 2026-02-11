inv_knob_label_pan(char *label, float value, float min, float max)
{
	float center;
	gint pan;

	center = (max+min)/2;

	if(value < center)
	{
		pan=-100 * (value/(center-min));
		if(pan==0) {
			sprintf(label,"Centre");
		} else {
			sprintf(label,"%i%% L",pan);
		}
	} else {
		pan=100 * (value/(max-center));
		if(pan==0) {
			sprintf(label,"Centre");
		} else {
			sprintf(label,"%i%% R",pan);
		}
	}
}
