divMatrixCmplx(Matrix *a, Cmplx *b){
   int i, j;
   Number *n1;
   Number **ptr1, **ptr2;
   Matrix *p = newMatrix();

   if(a == NULL) { fprintf(stderr, "divMatrixCmplx(NULL)\n"); exit(0); }


   p->data = mallocData(NULL, a->rows, a->cols);
   p->rows = a->rows;
   p->cols = a->cols;


   for(i=0; i<a->rows; i++)
      for(j=0; j<a->cols; j++){
         ptr1 = a->data + (a->cols * i) + j;
         ptr2 = p->data + (a->cols * i) + j;
         *ptr2 = divNumber(*ptr1, (n1=setNumberCmplx(newNumber(), b)));
         freeNumber(n1);
      }

   return p;
}
