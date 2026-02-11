cb_vertex(void * vertex_data, void * x)
{
  SbGLUTessellator * t = static_cast<SbGLUTessellator *>(x);

  switch (t->triangletessmode) {
  case GL_TRIANGLE_FAN:
    if (t->vertexidx == 0) { t->vertexdata[0] = vertex_data; }
    else if (t->vertexidx == 1) { t->vertexdata[1] = vertex_data; }
    else {
      t->callback(t->vertexdata[0], t->vertexdata[1], vertex_data, t->cbdata);
      t->vertexdata[1] = vertex_data;
    }
    break;

  case GL_TRIANGLE_STRIP:
    if (t->vertexidx == 0) { t->vertexdata[0] = vertex_data; }
    else if (t->vertexidx == 1) { t->vertexdata[1] = vertex_data; }
    else {
      t->callback(t->vertexdata[t->stripflipflop ? 1 : 0],
                  t->vertexdata[t->stripflipflop ? 0 : 1],
                  vertex_data,
                  t->cbdata);

      t->vertexdata[0] = t->vertexdata[1];
      t->vertexdata[1] = vertex_data;
      t->stripflipflop = t->stripflipflop ? FALSE : TRUE;
    }
    break;

  case GL_TRIANGLES:
    if (t->vertexidx % 3 == 0) { t->vertexdata[0] = vertex_data; }
    else if (t->vertexidx % 3 == 1) { t->vertexdata[1] = vertex_data; }
    else if (t->vertexidx % 3 == 2) {
      t->callback(t->vertexdata[0], t->vertexdata[1], vertex_data, t->cbdata);
    }
    break;

  default:
    assert(FALSE);
    break;
  }

  t->vertexidx++;
}
