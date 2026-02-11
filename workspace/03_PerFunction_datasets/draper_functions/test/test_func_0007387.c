xsh_rec_list_get_lambda_max( xsh_rec_list* list)
{
  double lambda_max =0.0;
  int i;

  XSH_ASSURE_NOT_NULL( list);

  for( i=0; i< list->size; i++){
    if ( list->list[i].lambda != NULL){
      double lambda;

      lambda = list->list[i].lambda[list->list[i].nlambda-1];
      if ( lambda  > lambda_max){
        lambda_max = lambda;
      }
    }
  }
  cleanup:
    return lambda_max;
}
