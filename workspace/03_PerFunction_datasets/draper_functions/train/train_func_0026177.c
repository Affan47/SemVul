data_get_transaction_rate(DATA this)
{
  if((this->count==0)||(this->elapsed==0))
    return 0;
  return (this->count / this->elapsed);
}
