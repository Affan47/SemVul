svm_read_solution_fp(FILE *fp) {
  SVM_Solution *sol = (SVM_Solution *)malloc(sizeof(SVM_Solution));
  size_t unused;

  if (!fp) {
    if (SVM_DEBUG_MODE) {
      fprintf(stderr, "svm_read_solution: bad file pointer.\n");
    }
    free(sol);
    return NULL;
  }

  sol->theta = vector_read_bin_fp(fp);
  if (!sol->theta) {
    if (SVM_DEBUG_MODE) {
      fprintf(stderr, "read_solution: Bad file.\n");
    }
    free(sol);
    return NULL;
  }
  sol->SV = matr_read_bin_fp(fp);
  unused = fread(&(sol->num_examples), sizeof(int), 1, fp);
  unused = fread(&(sol->max_train_val), sizeof(int), 1, fp);
  return sol;
}
