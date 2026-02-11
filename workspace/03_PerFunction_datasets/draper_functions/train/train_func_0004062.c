SparseMatrix_import_binary(char *name){
  SparseMatrix A = NULL;
  int m, n, nz, nzmax, type, format, property, iread;
  size_t sz;
  FILE *f;

  f = fopen(name, "rb");

  if (!f) return NULL;
  iread = fread(&m, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&n, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&nz, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&nzmax, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&type, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&format, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&property, sizeof(int), 1, f);
  if (iread != 1) return NULL;
  iread = fread(&sz, sizeof(size_t), 1, f);
  if (iread != 1) return NULL;

  A = SparseMatrix_general_new(m, n, nz, type, sz, format);
  A->nz = nz;
  A->property = property;

  if (format == FORMAT_COORD){
    iread = fread(A->ia, sizeof(int), A->nz, f);
    if (iread != A->nz) return NULL;
  } else {
    iread = fread(A->ia, sizeof(int), A->m + 1, f);
    if (iread != A->m + 1) return NULL;
  }
  iread = fread(A->ja, sizeof(int), A->nz, f);
  if (iread != A->nz) return NULL;

  if (A->size > 0) {
    iread = fread(A->a, A->size, A->nz, f);
    if (iread != A->nz) return NULL;
  }
  fclose(f);
  return A;
}
