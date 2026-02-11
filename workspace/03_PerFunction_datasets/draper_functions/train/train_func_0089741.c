activate()
{
    glViewport(static_cast<GLsizei>(d_area.d_left),
               static_cast<GLsizei>(d_area.d_top),
               static_cast<GLsizei>(d_area.getWidth()),
               static_cast<GLsizei>(d_area.getHeight()));

    if (!d_matrixValid)
        updateMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(d_matrix);
}
