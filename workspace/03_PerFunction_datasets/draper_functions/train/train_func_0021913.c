expNumber(Number *a){
   Number *c = newNumber();

   if(a == NULL){ fprintf(stderr, "expNumber(NULL)\n"); exit(0); }

   switch(a->type){
      case REAL:
         c->type = REAL;
         c->data = expReal(a->data);
         break;
      case COMPLEX:
         c->type = COMPLEX;
         c->data = expCmplx(a->data);
         break;
      case MATRIX:
         c->type = MATRIX;
         invalidTyprError("exp");
         c->data = NULL;
         break;
      default:
         fprintf(stderr, "Error: Unknown number type\n");
         exit(0);
   }
   if(c->data == NULL){ free(c); c = NULL; }
   return c;
}
