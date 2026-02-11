range() const
{
   if      ( lb_ == ub_ )                                  return 0.0;
   else if ( lb_ == -COIN_DBL_MAX && ub_ == COIN_DBL_MAX ) return 0.0;
   else if ( lb_ == -COIN_DBL_MAX )                        return 0.0;
   else if ( ub_ == COIN_DBL_MAX )                         return 0.0;
   else                                                    return ub_ - lb_;
}
