col_name(struct csa *csa, int j)
{
      char *f;
      xassert(1 <= j && j <= csa->P->n);
      if (csa->P->col[j]->name == NULL ||
          csa->deck && strlen(csa->P->col[j]->name) > 8)
         sprintf(csa->field, "C%07d", j);
      else
      {  strcpy(csa->field, csa->P->col[j]->name);
         for (f = csa->field; *f != '\0'; f++)
            if (*f == ' ') *f = '_';
      }
      return csa->field;
}
