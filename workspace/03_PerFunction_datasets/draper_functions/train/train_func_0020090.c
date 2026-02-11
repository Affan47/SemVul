printAMotor (PrintingContext &c, dxJoint *j)
{
	dxJointAMotor *a = (dxJointAMotor*) j;
	c.print ("num",a->num);
	c.print ("mode",a->mode);
	c.printIndent();
	fprintf (c.file,"rel = {%d,%d,%d},\n",a->rel[0],a->rel[1],a->rel[2]);
	c.print ("axis1",a->axis[0]);
	c.print ("axis2",a->axis[1]);
	c.print ("axis3",a->axis[2]);
	for (int i=0; i<3; i++) printLimot (c,a->limot[i],i+1);
	c.print ("angle1",a->angle[0]);
	c.print ("angle2",a->angle[1]);
	c.print ("angle3",a->angle[2]);
}
