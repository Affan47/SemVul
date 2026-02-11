glmAddGroup(GLMmodel* model, char* name)
{
  GLMgroup* group;

  group = glmFindGroup(model, name);
  if (!group) {
    group = (GLMgroup*)malloc(sizeof(GLMgroup));
    group->name = strdup(name);
    group->material = 0;
    group->numtriangles = 0;
    group->triangles = NULL;
    group->next = model->groups;
    model->groups = group;
    model->numgroups++;
  }

  return group;
}
