read_objectA(ObjIO *obj, FILE *fp)
{
  char word[MAX_NAME];
  int i;

  CHECK(1, fscanf(fp," name %[^\n\r]",word));
  if (strcmp(word,"NULL") == 0) {
    obj->name = NULL;
  } else {
    if (word[0] != '\"' || word[strlen(word)-1] != '\"' ) {
      printf("Error in object name format: %s\n", word);
      obj->name = NULL;
    } else {
      word[strlen(word)-1] = '\0';
      obj->name = strdup(word+1);
    }
  }
  CHECK(1,fscanf(fp," numMaterials %ld",&obj->numMaterials));
  obj->material = new_material(obj->numMaterials);
  for (i=0; i < obj->numMaterials; ++i) {
    read_materialA(obj->material + i, fp);
  }
}
