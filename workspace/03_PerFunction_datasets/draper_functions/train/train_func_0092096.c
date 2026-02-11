getc1(c, c1)
     Character *c;
     int c1;
{
    int GL_save, GR_save;

    switch(c1) {
      case 0x8e:
	GL_save = input_GL;
	GR_save = input_GR;
	input_GL = SETG2;
	input_GR = SETG2;
	getkanji(c);
	input_GL = GL_save;
	input_GR = GR_save;
	return;
      case 0x8f:
	GL_save = input_GL;
	GR_save = input_GR;
	input_GL = SETG3;
	input_GR = SETG3;
	getkanji(c);
	input_GL = GL_save;
	input_GR = GR_save;
	return;
      default:
	c->type = OTHER; c->c1 = c1; return;
    }
}
