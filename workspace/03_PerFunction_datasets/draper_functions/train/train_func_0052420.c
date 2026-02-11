dVinvt_dR(const CPose3D &P, CMatrixFixedNumeric<double,3,9> &J)
		{
			CArrayDouble<3>  a;
			CMatrixDouble33  B(UNINITIALIZED_MATRIX);

			const CMatrixDouble33 &R = P.getRotationMatrix();
			const CArrayDouble<3> &t = P.m_coords;

			const double d = 0.5*( R(0,0)+R(1,1)+R(2,2)-1);

			if (d>0.9999)
			{
				a[0]=a[1]=a[2]=0;
				B.zeros();
			}
			else
			{
				const double theta = acos(d);
				const double theta2 = square(theta);
				const double oned2 = (1-square(d));
				const double sq = std::sqrt(oned2);
				const double cot = 1./tan(0.5*theta);
				const double csc2 = square(1./sin(0.5*theta));

				CMatrixDouble33 skewR(UNINITIALIZED_MATRIX);
				CArrayDouble<3>  vr;
				deltaR(R,vr);
				mrpt::math::skew_symmetric3(vr,skewR);

				CArrayDouble<3> skewR_t;
				skewR.multiply_Ab(t,skewR_t);

				skewR_t*= -(d*theta-sq)/(8*pow(sq,3));
				a = skewR_t;

				CMatrixDouble33  skewR2(UNINITIALIZED_MATRIX);
				skewR2.multiply_AB(skewR,skewR);

				CArrayDouble<3> skewR2_t;
				skewR2.multiply_Ab(t,skewR2_t);
				skewR2_t*= (((theta*sq-d*theta2)*(0.5*theta*cot-1))-theta*sq*((0.25*theta*cot)+0.125*theta2*csc2-1))/(4*theta2*square(oned2));
				a += skewR2_t;

				mrpt::math::skew_symmetric3(t,B);
				B *=-0.5*theta/(2*sq);

				B += -(theta*cot-2)/(8*oned2) * ddeltaRt_dR(P);
			}
			M3x9(a,B,J);
		}
