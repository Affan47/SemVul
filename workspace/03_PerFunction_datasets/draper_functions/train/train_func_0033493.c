projectorigin(	const btVector3& a,
				const btVector3& b,
				const btVector3& c,
				btScalar* w,U& m)
			{
				static const U		imd3[]={1,2,0};
				const btVector3*	vt[]={&a,&b,&c};
				const btVector3		dl[]={a-b,b-c,c-a};
				const btVector3		n=btCross(dl[0],dl[1]);
				const btScalar		l=n.length2();
				if(l>GJK_SIMPLEX3_EPS)
				{
					btScalar	mindist=-1;
					btScalar	subw[2]={0.f,0.f};
					U			subm(0);
					for(U i=0;i<3;++i)
					{
						if(btDot(*vt[i],btCross(dl[i],n))>0)
						{
							const U			j=imd3[i];
							const btScalar	subd(projectorigin(*vt[i],*vt[j],subw,subm));
							if((mindist<0)||(subd<mindist))
							{
								mindist		=	subd;
								m			=	static_cast<U>(((subm&1)?1<<i:0)+((subm&2)?1<<j:0));
								w[i]		=	subw[0];
								w[j]		=	subw[1];
								w[imd3[j]]	=	0;
							}
						}
					}
					if(mindist<0)
					{
						const btScalar	d=btDot(a,n);
						const btScalar	s=btSqrt(l);
						const btVector3	p=n*(d/l);
						mindist	=	p.length2();
						m		=	7;
						w[0]	=	(btCross(dl[1],b-p)).length()/s;
						w[1]	=	(btCross(dl[2],c-p)).length()/s;
						w[2]	=	1-(w[0]+w[1]);
					}
					return(mindist);
				}
				return(-1);
			}
