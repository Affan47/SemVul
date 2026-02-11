IsEqualSign( std::size_t i ) const
{
  if( i >= tokens_.size() )return false;
  return tokens_[i]->IsaEqualSign();
}
