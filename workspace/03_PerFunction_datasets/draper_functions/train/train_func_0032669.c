HTS_Model_load_pdf(HTS_Model * model, HTS_File * fp, size_t vector_length, size_t num_windows, HTS_Boolean is_msd)
{
   unsigned int i;
   size_t j, k;
   HTS_Boolean result = TRUE;
   size_t len;


   if (model == NULL || fp == NULL || model->ntree <= 0) {
      HTS_error(1, "HTS_Model_load_pdf: File for pdfs is not specified.\n");
      return FALSE;
   }


   model->vector_length = vector_length;
   model->num_windows = num_windows;
   model->is_msd = is_msd;
   model->npdf = (size_t *) HTS_calloc(model->ntree, sizeof(size_t));
   model->npdf -= 2;

   for (j = 2; j <= model->ntree + 1; j++) {
      if (HTS_fread_little_endian(&i, sizeof(unsigned int), 1, fp) != 1) {
         result = FALSE;
         break;
      }
      model->npdf[j] = (size_t) i;
   }
   for (j = 2; j <= model->ntree + 1; j++) {
      if (model->npdf[j] <= 0) {
         HTS_error(1, "HTS_Model_load_pdf: # of pdfs at %d-th state should be positive.\n", j);
         result = FALSE;
         break;
      }
   }
   if (result == FALSE) {
      model->npdf += 2;
      free(model->npdf);
      HTS_Model_initialize(model);
      return FALSE;
   }
   model->pdf = (float ***) HTS_calloc(model->ntree, sizeof(float **));
   model->pdf -= 2;

   if (is_msd)
      len = model->vector_length * model->num_windows * 2 + 1;
   else
      len = model->vector_length * model->num_windows * 2;
   for (j = 2; j <= model->ntree + 1; j++) {
      model->pdf[j] = (float **) HTS_calloc(model->npdf[j], sizeof(float *));
      model->pdf[j]--;
      for (k = 1; k <= model->npdf[j]; k++) {
         model->pdf[j][k] = (float *) HTS_calloc(len, sizeof(float));
         if (HTS_fread_little_endian(model->pdf[j][k], sizeof(float), len, fp) != len)
            result = FALSE;
      }
   }
   if (result == FALSE) {
      HTS_Model_clear(model);
      return FALSE;
   }
   return TRUE;
}
