VibGenList(GLuint viblist)
{
	if (glIsList(viblist) == GL_TRUE)
		glDeleteLists(viblist,1);

        viblist = glGenLists(1);
	glNewList(viblist, GL_COMPILE);

	draw_vectors();

	glEndList();
	return viblist;
}
