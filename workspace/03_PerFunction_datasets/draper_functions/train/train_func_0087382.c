m_xformptonly(GLdouble pin[3], GLdouble pout[3])
{
    int	i;
    GLdouble	ptemp[3];
    mat_t	*m = &matstack[mattop];

    if (identitymat) {
	for (i = 0; i < 3; i++) {
	    pout[i] = pin[i];
	}
	return;
    }
     for (i = 0; i < 3; i++) {
	ptemp[i] = pin[0]*m->mat[0][i] +
		   pin[1]*m->mat[1][i] +
		   pin[2]*m->mat[2][i] +
		   m->mat[3][i];
    }
    for (i = 0; i < 3; i++) {
	pout[i] = ptemp[i];
    }
}
