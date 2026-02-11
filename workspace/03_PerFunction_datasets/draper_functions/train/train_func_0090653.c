gsd_rot(float angle, char axis)
{
    GLfloat x;
    GLfloat y;
    GLfloat z;

    switch (axis) {
    case 'x':
    case 'X':

	x = 1.0;
	y = 0.0;
	z = 0.0;

	break;
    case 'y':
    case 'Y':

	x = 0.0;
	y = 1.0;
	z = 0.0;

	break;
    case 'z':
    case 'Z':

	x = 0.0;
	y = 0.0;
	z = 1.0;

	break;
    default:

	G_warning(_("gsd_rot(): %c is an invalid axis "
		    "specification. Rotation ignored. "
		    "Please advise GRASS developers of this error"), axis);
	return;
    }

    glRotatef((GLfloat) angle, x, y, z);

    return;
}
