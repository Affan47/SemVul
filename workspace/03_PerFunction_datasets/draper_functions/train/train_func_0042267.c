projectorigin(	const btVector3& a,
				const btVector3& b,
				const btVector3& c,
				const btVector3& d,
				btScalar* w,U& m)
			{
				static const U		imd3[]={1,2,0};
				const btVector3*	vt[]={&a,&b,&c,&d};
				const btVector3		dl[]={a-d,b-d,c-d};
				const btScalar		vl=det(dl[0],dl[1],dl[2]);
				const bool			ng=(vl*btDot(a,btCross(b-c,a-b)))<=0;
				if(ng&&(btFabs(vl)>GJK_SIMPLEX4_EPS))
				{
					btScalar	mindist=-1;
					btScalar	subw[3]={0.f,0.f,0.f};
					U			subm(0);
					for(U i=0;i<3;++i)
					{
						const U			j=imd3[i];
						const btScalar	s=vl*btDot(d,btCross(dl[i],dl[j]));
						if(s>0)
						{
							const btScalar	subd=projectorigin(*vt[i],*vt[j],d,subw,subm);
							if((mindist<0)||(subd<mindist))
							{
								mindist		=	subd;
								m			=	static_cast<U>((subm&1?1<<i:0)+
									(subm&2?1<<j:0)+
									(subm&4?8:0));
								w[i]		=	subw[0];
								w[j]		=	subw[1];
								w[imd3[j]]	=	0;
								w[3]		=	subw[2];
							}
						}
					}
					if(mindist<0)
					{
						mindist	=	0;
						m		=	15;
						w[0]	=	det(c,b,d)/vl;
						w[1]	=	det(a,c,d)/vl;
						w[2]	=	det(b,a,d)/vl;
						w[3]	=	1-(w[0]+w[1]+w[2]);
					}
					return(mindist);
				}
				return(-1);
			}
