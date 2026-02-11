glmWeld(GLMmodel* model, GLfloat epsilon)
{
  GLfloat* vectors;
  GLfloat* copies;
  GLuint   numvectors;
  GLuint   i;


  numvectors = model->numvertices;
  vectors  = model->vertices;
  copies = _glmWeldVectors(vectors, &numvectors, epsilon);

  verbose(1, "glmWeld(): %d redundant vertices.", model->numvertices - numvectors - 1);

  for (i = 0; i < model->numtriangles; i++) {
    T(i).vindices[0] = static_cast<GLuint>(vectors[3 * T(i).vindices[0] + 0]);
    T(i).vindices[1] = static_cast<GLuint>(vectors[3 * T(i).vindices[1] + 0]);
    T(i).vindices[2] = static_cast<GLuint>(vectors[3 * T(i).vindices[2] + 0]);
  }


  free(vectors);


  model->numvertices = numvectors;
  model->vertices = (GLfloat*)malloc(sizeof(GLfloat) *
                                     3 * (model->numvertices + 1));


  for (i = 1; i <= model->numvertices; i++) {
    model->vertices[3 * i + 0] = copies[3 * i + 0];
    model->vertices[3 * i + 1] = copies[3 * i + 1];
    model->vertices[3 * i + 2] = copies[3 * i + 2];
  }

  free(copies);
}
