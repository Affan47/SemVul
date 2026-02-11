Clp_printModel(Clp_Simplex * model, const char * prefix)
{
     ClpSimplex *clp_simplex = model->model_;
     int numrows    = clp_simplex->numberRows();
     int numcols    = clp_simplex->numberColumns();
     int numelem    = clp_simplex->getNumElements();
     const CoinBigIndex *start = clp_simplex->matrix()->getVectorStarts();
     const int *index     = clp_simplex->matrix()->getIndices();
     const double *value  = clp_simplex->matrix()->getElements();
     const double *collb  = model->model_->columnLower();
     const double *colub  = model->model_->columnUpper();
     const double *obj    = model->model_->objective();
     const double *rowlb  = model->model_->rowLower();
     const double *rowub  = model->model_->rowUpper();
     printf("%s numcols = %i, numrows = %i, numelem = %i\n",
            prefix, numcols, numrows, numelem);
     printf("%s model = %p, start = %p, index = %p, value = %p\n",
            prefix, reinterpret_cast<const void *>(model), reinterpret_cast<const void *>(start), reinterpret_cast<const void *>(index), reinterpret_cast<const void *>(value));
     clp_simplex->matrix()->dumpMatrix(NULL);
     {
          int i;
          for (i = 0; i <= numcols; i++)
               printf("%s start[%i] = %i\n", prefix, i, start[i]);
          for (i = 0; i < numelem; i++)
               printf("%s index[%i] = %i, value[%i] = %g\n",
                      prefix, i, index[i], i, value[i]);
     }

     printf("%s collb = %p, colub = %p, obj = %p, rowlb = %p, rowub = %p\n",
            prefix, reinterpret_cast<const void *>(collb), reinterpret_cast<const void *>(colub), reinterpret_cast<const void *>(obj), reinterpret_cast<const void *>(rowlb), reinterpret_cast<const void *>(rowub));
     printf("%s optimization direction = %g\n", prefix, Clp_optimizationDirection(model));
     printf("  (1 - minimize, -1 - maximize, 0 - ignore)\n");
     {
          int i;
          for (i = 0; i < numcols; i++)
               printf("%s collb[%i] = %g, colub[%i] = %g, obj[%i] = %g\n",
                      prefix, i, collb[i], i, colub[i], i, obj[i]);
          for (i = 0; i < numrows; i++)
               printf("%s rowlb[%i] = %g, rowub[%i] = %g\n",
                      prefix, i, rowlb[i], i, rowub[i]);
     }
}
