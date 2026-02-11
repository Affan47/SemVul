static_glu_vertex (double* vertex, glu_tessdata *data)
{
int temp[4];
double point[3];

switch (data->polygon)
  {
  case GL_TRIANGLES:
  if ((data->vertex + 1) % 3 == 0)
    {
    temp[0] = data->vcount / 3 - 2;
    temp[1] = data->vcount / 3 - 1;
    temp[2] = data->vcount / 3 - 0;
    temp[3] = -1;

    data->ocount += 4;
    gamgi_engine_iarray_push(data->order, temp);
    }
  break;

  case GL_TRIANGLE_STRIP:
  if (data->vertex > 1)
    {
    temp[0] = data->vcount / 3 - 2;
    temp[1] = data->vcount / 3 - 1;
    temp[2] = data->vcount / 3 - 0;
    temp[3] = -1;

    data->ocount += 4;
    gamgi_engine_iarray_push(data->order, temp);
    }
  break;

  case GL_TRIANGLE_FAN:
  if (data->vertex > 1)
    {
    temp[0] = data->fancenter;
    temp[1] = data->vcount / 3 - 1;
    temp[2] = data->vcount / 3;
    temp[3] = -1;

    data->ocount += 4;
    gamgi_engine_iarray_push(data->order, temp);
    }
  break;
  }

point[0] = vertex[0] + data->x;
point[1] = vertex[1] + data->y;
point[2] = vertex[2] + data->z;

data->vcount += 3;
data->vertex++;

gamgi_engine_darray_push(data->vert, point);
}
