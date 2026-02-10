Comb(const BitField &bf)
{
  size_t i;
  if( !_isempty_sp(bf) && !_isfull() ){
    if( _isfull_sp(bf) ){
      SetAll();
    }else if( _isempty() ){
      memcpy(b, bf.b, nbytes);
      nset = bf.nset;
    }else{
      for(i = 0; i < nbytes; i++) b[i] |= bf.b[i];
      _recalc();
    }
  }
}
