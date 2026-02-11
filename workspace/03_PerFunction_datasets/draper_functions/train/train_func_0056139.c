grabPixels(int inColor, unsigned int width, unsigned int height)
{
    GLvoid *buffer;
    GLint   swapbytes, lsbfirst, rowlength;
    GLint   skiprows, skippixels, alignment;
    GLenum  format;
    unsigned int size;

    if (inColor) {
        format = GL_RGB;
        size = width * height * 3;
    } else {
        format = GL_LUMINANCE;
        size = width * height * 1;
    }

    buffer = (GLvoid *) malloc(size);
    if (buffer == NULL)
        return NULL;


    glGetIntegerv(GL_PACK_SWAP_BYTES, &swapbytes);
    glGetIntegerv(GL_PACK_LSB_FIRST, &lsbfirst);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &rowlength);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &skiprows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &skippixels);
    glGetIntegerv(GL_PACK_ALIGNMENT, &alignment);


    glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_PACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);


    glReadPixels(0, 0, width, height, format,
            GL_UNSIGNED_BYTE, (GLvoid *) buffer);


    glPixelStorei(GL_PACK_SWAP_BYTES, swapbytes);
    glPixelStorei(GL_PACK_LSB_FIRST, lsbfirst);
    glPixelStorei(GL_PACK_ROW_LENGTH, rowlength);
    glPixelStorei(GL_PACK_SKIP_ROWS, skiprows);
    glPixelStorei(GL_PACK_SKIP_PIXELS, skippixels);
    glPixelStorei(GL_PACK_ALIGNMENT, alignment);
    return buffer;
}
