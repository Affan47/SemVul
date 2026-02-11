draw_gear (struct gear *gear, GLfloat *transform,
           GLfloat x, GLfloat y, GLfloat angle, const GLfloat color[4])
{
    GLfloat model_view[16];
    GLfloat normal_matrix[16];
    GLfloat model_view_projection[16];
    int n;


    memcpy(model_view, transform, sizeof (model_view));
    translate(model_view, x, y, 0);
    rotate(model_view, 2 * M_PI * angle / 360.0, 0, 0, 1);


    memcpy (model_view_projection,
            ProjectionMatrix,
            sizeof(model_view_projection));
    multiply (model_view_projection, model_view);

    glUniformMatrix4fv (ModelViewProjectionMatrix_location, 1, GL_FALSE,
                        model_view_projection);


    memcpy (normal_matrix, model_view, sizeof (normal_matrix));
    invert (normal_matrix);
    transpose (normal_matrix);
    glUniformMatrix4fv (NormalMatrix_location, 1, GL_FALSE, normal_matrix);


    glUniform4fv (MaterialColor_location, 1, color);


    glBindBuffer (GL_ARRAY_BUFFER, gear->vbo);


    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE,
                           6 * sizeof(GLfloat), NULL);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE,
                           6 * sizeof(GLfloat), (GLfloat *) 0 + 3);


    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);


    for (n = 0; n < gear->nstrips; n++)
        glDrawArrays (GL_TRIANGLE_STRIP,
                      gear->strips[n].first,
                      gear->strips[n].count);


    glDisableVertexAttribArray (1);
    glDisableVertexAttribArray (0);
}
