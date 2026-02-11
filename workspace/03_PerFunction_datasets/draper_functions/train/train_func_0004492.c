GL_Upload8 (byte *data, int width, int height, int picmip, qboolean filter)
{
	unsigned	trans[512*256];
	int			i, s;
	int			p;

	s = width*height;

	if (s > sizeof(trans)/4)
		Com_Error (ERR_DROP, "GL_Upload8: too large");

	for (i=0 ; i<s ; i++)
    {
		p = data[i];
        trans[i] = d_8to24table[p];

        if (p == 255)
        {


            if (i > width && data[i-width] != 255)
                p = data[i-width];
            else if (i < s-width && data[i+width] != 255)
                p = data[i+width];
            else if (i > 0 && data[i-1] != 255)
                p = data[i-1];
            else if (i < s-1 && data[i+1] != 255)
                p = data[i+1];
            else
                p = 0;

            ((byte *)&trans[i])[0] = ((byte *)&d_8to24table[p])[0];
            ((byte *)&trans[i])[1] = ((byte *)&d_8to24table[p])[1];
            ((byte *)&trans[i])[2] = ((byte *)&d_8to24table[p])[2];
        }
    }
    return GL_Upload32 ((byte*)trans, width, height, picmip, filter, false);
}
