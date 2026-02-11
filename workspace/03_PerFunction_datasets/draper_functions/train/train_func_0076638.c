read_srfs(FILE *f, gint nbytes, lwObject *lwo)
{
  int guess_cnt = lwo->material_cnt;

  while (nbytes > 0) {
    lwMaterial *material;


    if (guess_cnt <= lwo->material_cnt) {
      guess_cnt += guess_cnt/2 + 4;
      lwo->material = g_realloc(lwo->material, sizeof(lwMaterial)*guess_cnt);
    }
    material = lwo->material + lwo->material_cnt++;


    nbytes -= read_string(f,material->name);


    material->r = 0.7;
    material->g = 0.7;
    material->b = 0.7;
  }
  lwo->material = g_realloc(lwo->material, sizeof(lwMaterial)*lwo->material_cnt);
}
