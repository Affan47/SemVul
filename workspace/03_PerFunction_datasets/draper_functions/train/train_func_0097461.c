lambda_delete(spot)
int spot;
{ int value = lambda_list[spot].value;
  if ( lambda_list[spot].prev )
    lambda_list[spot].prev->next = lambda_list[spot].next;
  else
  { lambda_heads[value] = lambda_list[spot].next;
    if ( (lambda_heads[value] == NULL) && (value == lambdamax) )
    {
      for ( ; (lambdamax >= 0) && (lambda_heads[lambdamax] == NULL) ; lambdamax-- ) ;
    }
  }
  if ( lambda_list[spot].next )
    lambda_list[spot].next->prev = lambda_list[spot].prev;
  lambda_count--;

}
