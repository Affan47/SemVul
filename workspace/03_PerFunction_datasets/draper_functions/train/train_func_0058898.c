FB(const What_d whatd,const Mesh & Th,const Mesh3::Element & K,const Rd &P, RNMK_ & val) const
     {
	 assert(val.N() >=4);
	 assert(val.M()==3 );

	 val=0;

	 R cc =1./(d*K.mesure());
	 R ci[4]={ cc*K.faceOrient(0),cc*K.faceOrient(1),cc*K.faceOrient(2),cc*K.faceOrient(3)};

	 if (whatd & Fop_D0)
	   {
	       R3 X=K(P);
	       int k=0;
	       for(int i=0;i<4;++i)
		 { R3 wi=(X-K[i])*ci[i];
		     val(i,0,op_id) = wi.x ;
		     val(i,1,op_id) = wi.y ;
		     val(i,2,op_id) = wi.z ;

		 }
	   }

	 if (whatd & Fop_D1)
	   {
	       RN_ Ci(ci,4);
	       if (whatd & Fop_dx)
		   val('.',0,op_dx) = Ci;
	       if (whatd & Fop_dy)
		   val('.',1,op_dy) = Ci;
	       if (whatd & Fop_dz)
		   val('.',2,op_dz) = Ci;

	   }

     }
