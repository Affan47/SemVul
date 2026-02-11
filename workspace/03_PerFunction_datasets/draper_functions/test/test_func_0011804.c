bind() const
{
	if(numTexUnits < 1) return;

#ifdef HAVE_MULTITEX
	for(int i = 0; i < numTexUnits; i++)
	{
		mglActiveTextureARB(GL_TEXTURE0_ARB + i);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texUnits[i].handle);
	}
#else
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texUnits[0].handle);
#endif
}
