findAFitWithSphere(SimpleParticle& Po, const vector<SimpleParticle*>& NL)
    {

      bool find_a_fit ;
      Vec3 M;
      double r;
      int id=Po.getID();

      if(NL.size()<3){
	find_a_fit=false;

      } else {
	Vec3 Pos1=m_center;
	Vec3 Pos2=NL[0]->getPos();
	Vec3 Pos3=NL[1]->getPos();
	Vec3 Pos4=NL[2]->getPos();
	double r1=-1.0*m_radius;
	double r2=NL[0]->getRad();
	double r3=NL[1]->getRad();
	double r4=NL[2]->getRad();

	find_a_fit=Sphere3D::FillIn(Pos1,Pos2,Pos3,Pos4,r1,r2,r3,r4,M,r);
	Po=SimpleParticle(M,r,id,m_tag);

      }

      return find_a_fit ;
    }
