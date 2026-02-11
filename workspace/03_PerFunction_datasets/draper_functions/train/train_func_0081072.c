glmUVTexture(GLMmodel* model, float h, float w)
{
  GLMgroup *group;
  GLuint i;

  if(!model)return;
  if(!(model->uvtexcoords))return;

  if (model->texcoords)
    free(model->texcoords);

  model->numtexcoords = model->numuvtexcoords;
  model->texcoords=(GLfloat*)malloc(sizeof(GLfloat)*2*(model->numuvtexcoords+1));


  for(i = 1; i <= model->numtexcoords; i++) {
    model->texcoords[2*i+0] = model->uvtexcoords[2*i+0]*w;
    model->texcoords[2*i+1] = model->uvtexcoords[2*i+1]*h;
  }


  group = model->groups;
  while(group) {
    for(i = 0; i < group->numtriangles; i++) {
      T(group->triangles[i]).tindices[0] = T(group->triangles[i]).uvtindices[0];
      T(group->triangles[i]).tindices[1] = T(group->triangles[i]).uvtindices[1];
      T(group->triangles[i]).tindices[2] = T(group->triangles[i]).uvtindices[2];
    }
    group = group->next;
  }
  verbose(1, "glmUVTexture(): generated %d UV texture coordinates", model->numtexcoords);
}
