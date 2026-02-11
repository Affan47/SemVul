operator=( const ZpzDom<Log16>& F)
{

	F.assign(const_cast<Element&>(one),F.one);
	F.assign(const_cast<Element&>(zero),F.zero);
	F.assign(const_cast<Element&>(mOne),F.mOne);


  if (this->numRefs) {
    (*(this->numRefs))--;
#ifdef GIVARO_DEBUG
    std::cout << *(this->numRefs) << " Crefs, p="<<this->_p<<" \n";
#endif
    if ((*(this->numRefs))==0) {
#ifdef GIVARO_DEBUG
      std::cout << "zero : " << zero << std::endl;
      std::cout << "Ddestroying, p="<<residu()<<"\n";
#endif
      delete [] _tab_value2rep;
      delete [] _tab_rep2value;
      delete [] _tab_mul;
      delete [] _tab_mone;
      delete [] _tab_pone;


      delete numRefs;
    }
  }

  this->_p = F.residu();
  this->_pmone = F._pmone;
  this->_tab_value2rep = F._tab_value2rep;
  this->_tab_rep2value = F._tab_rep2value;
  this->_tab_mul = F._tab_mul;
  this->_tab_div = F._tab_div;
  this->_tab_neg = F._tab_neg;
  this->_tab_mone = F._tab_mone;
  this->_tab_pone = F._tab_pone;
  this->_tab_addone = F._tab_addone;
  this->_tab_subone = F._tab_subone;
  this->numRefs = F.numRefs;
  (*(this->numRefs))++;
#ifdef GIVARO_DEBUG
  std::cout << *(this->numRefs) << " Erefs, p = "<<this->_p<<"\n";
#endif

  return *this;
}
