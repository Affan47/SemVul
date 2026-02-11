write(int m){
  int i = 0;
  Term *p = this;
  while(p){
    i++;
    if ((p->expo) == 0){
      std::cout << p->coeff << std::endl;
    }
    else{
      if (p->ind2 == -1){
	if (p->ind1 < m)
	  std::cout << p->coeff << "u[" << p->ind1 << "," << p->expo << "] ";
	else
	  std::cout << p->coeff << "x[" << p->ind1 - m<< "," << p->expo << "] ";
      }
      else{
	if (p->ind1 < m)
	  std::cout << p->coeff << "u[" << p->ind1 << "]";
	else{
	  std::cout << p->coeff << "x[" << p->ind1 - m<< "]";
	}
	if (p->ind2 < m)
	  std::cout << "u[" << p->ind2 << "] ";
	else
	  std::cout <<  "x[" << p->ind2 - m<< "] ";
      }
    }
    p = p-> next;
  }
  std::cout << "\n";
}
