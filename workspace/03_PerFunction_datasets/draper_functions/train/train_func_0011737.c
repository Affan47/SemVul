IoRange_setRange(IoRange *self, IoObject *locals, IoMessage *m)
{


	IoObject *start = IoMessage_locals_valueArgAt_(m, locals, 0);
	IoObject *end = IoMessage_locals_valueArgAt_(m, locals, 1);
	IoNumber *increment;

	if (IoMessage_argCount(m) == 3)
		increment = IoMessage_locals_numberArgAt_(m, locals, 2);
	else
	{
	  if( IOREF(start) < IOREF(end))
	    increment = IONUMBER(1);
	  else
      increment = IONUMBER(-1);
  }

	DATA(self)->start = IOREF(start);
	DATA(self)->end = IOREF(end);
	DATA(self)->curr = DATA(self)->start;
	DATA(self)->increment = IOREF(increment);
	DATA(self)->index = IONUMBER(0);

	return self;
}
