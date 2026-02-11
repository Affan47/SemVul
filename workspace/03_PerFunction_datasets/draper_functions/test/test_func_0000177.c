checkGLError()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {

	return true;
    }
    return false;
}
