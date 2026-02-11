LinuxGetJoystickPosition( double *x1, double *y1,
	double *rudder, double *throttle, int *switches)
{
	struct js_event jevent;
	#define AXIS_MAX 4

	static double axis[AXIS_MAX] = {0,0,-2,-2};


	int previous;
	static int buttons = 0;
	static int release = 0;
	int result;
	int b;

	if(fd == -1)
		return -1;


	if((buttons & 1) && (release & 1 ))
		buttons &= ~1;
	if((buttons & 2) && (release & 2 ))
		buttons &= ~2;
	release = 0;

	previous = buttons;

	while((result = read(fd, &jevent, sizeof(jevent)))!=-1)
	{
		switch(jevent.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_BUTTON:
			b = 1 << jevent.number;
			if(jevent.value)
			{
				buttons |= b;
				release &= ~b;
			}
			else
			{

				if(previous & b)
				{
					buttons &= ~b;
					release &= ~b;
					previous &= ~b;
				}
				else
				{
					release |= b;
				}
			}
			break;
		case JS_EVENT_AXIS:
			if(jevent.number < AXIS_MAX)
				axis[jevent.number] =
					-1 * (double)jevent.value/32768.0;
		}
	}
	*x1 = axis[0];
	*y1 = axis[1];
	*rudder = axis[2];
	*throttle = axis[3];
	*switches = buttons;

	return 0;
}
