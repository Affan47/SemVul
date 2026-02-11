shape_from_contour(SHAPE **oshape, const int *contour_x,
                        const int *contour_y, const int ncontour)
{
   SHAPE *shape;
   ROW *row;
   int ret, i, xmin, ymin, xmax, ymax;


   contour_limits(&xmin, &ymin, &xmax, &ymax,
                  contour_x, contour_y, ncontour);


   if((ret = alloc_shape(&shape, xmin, ymin, xmax, ymax)))

      return(ret);


   for(i = 0; i < ncontour; i++){


      row = shape->rows[contour_y[i]-ymin];


      if(in_int_list(contour_x[i], row->xs, row->npts) < 0){

         if(row->npts >= row->alloc){


            fprintf(stderr,
                    "ERROR : shape_from_contour : row overflow\n");
            return(-260);
         }


         row->xs[row->npts++] = contour_x[i];
      }

   }


   for(i = 0; i < shape->nrows; i++)

      sort_row_on_x(shape->rows[i]);


   *oshape = shape;


   return(0);
}
