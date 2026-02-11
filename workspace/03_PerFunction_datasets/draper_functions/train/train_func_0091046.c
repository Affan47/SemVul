getControllerForParam(unsigned paramIdx)
{
	for (unsigned int i=0; i<MAX_CC; i++) {
		if (midi_controllers[i] &&
			midi_controllers[i]->GetId() == i) {
			return i;
		}
	}
	return -1;
}
