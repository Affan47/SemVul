radToPos(char axis,double nrad) {

	if (axis==Pan)  return (long) (nrad / panResolution);
	else  return (long) (nrad / tiltResolution);
}
