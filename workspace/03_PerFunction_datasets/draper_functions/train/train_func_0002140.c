Add(Key k,Key op,OneOperator *p0,OneOperator *p1,
      OneOperator *p2,OneOperator *p3,OneOperator *p4,OneOperator *p5,OneOperator *p6)
  {
      iterator i= m.find(k);
      if (i==m.end())
	{
	    Value poly0=Value(atype<Polymorphic*>(),new Polymorphic(),listofvar);
	    i=m.insert(pair<const Key,Value>(k,poly0)).first;
	    listofvar= &*i;
	}
      const Polymorphic * p= dynamic_cast<const Polymorphic *>(i->second.second);
      if ( !p) {
	  if(mpirank==0)
	      cerr << k << " is not a Polymorphic id " << endl;
	  CompileError();
      }
      p->Add(op,p0,p1,p2,p3,p4,p5,p6);
  }
