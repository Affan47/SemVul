FuzzyFlakesDrawFlake(Flake *flake, int XPos, int YPos, double AngleOffset, int Layer)
{
   int                 i;
   double              x, y, Angle, Radius;


   Radius = (double)(flake->Radius - Layer * 5);

   for (i = 1; i <= flake->Arms; i++)
     {
	int                 Diameter;

	Diameter = (flake->BorderThickness * 2 + flake->Thickness) / Layer;

	Angle = ((2 * M_PI) / flake->Arms) * i + AngleOffset;

	y = (int)(sin(Angle) * Radius);
	x = (int)(cos(Angle) * Radius);

	flake->GCValues.line_width = Diameter;
	XFreeGC(flake->dpy, flake->GCVar);
	flake->GCVar =
	   XCreateGC(flake->dpy, flake->DB.b, flake->GCFlags,
		     &flake->GCValues);
	XSetForeground(flake->dpy, flake->GCVar, flake->BordColor);
	XDrawLine(flake->dpy, flake->DB.b, flake->GCVar, XPos, YPos,
		  XPos + x, YPos + y);
     }

   for (i = 1; i <= flake->Arms; i++)
     {

	Angle = ((2 * M_PI) / flake->Arms) * i + AngleOffset;

	y = (int)(sin(Angle) * Radius);
	x = (int)(cos(Angle) * Radius);

	flake->GCValues.line_width = flake->Thickness / Layer;
	XFreeGC(flake->dpy, flake->GCVar);
	flake->GCVar =
	   XCreateGC(flake->dpy, flake->DB.b, flake->GCFlags,
		     &flake->GCValues);
	XSetForeground(flake->dpy, flake->GCVar, flake->ForeColor);
	XDrawLine(flake->dpy, flake->DB.b, flake->GCVar, XPos, YPos,
		  XPos + x, YPos + y);
     }
}
