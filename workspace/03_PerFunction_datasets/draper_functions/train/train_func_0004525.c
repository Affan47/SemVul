store_clsf_DS_classes( clsf_DS clsf, class_DS *check_classes, int length)
{
   int i, n_classes;
   class_DS *classes;

   n_classes = clsf->n_classes;
   classes = clsf->classes;

   for (i=0; i<n_classes; i++) {

	 store_class_DS(classes[i], clsf_DS_max_n_classes(clsf));


   }
   free(clsf->classes);
   clsf->classes = NULL;
   clsf->n_classes = 0;
}
