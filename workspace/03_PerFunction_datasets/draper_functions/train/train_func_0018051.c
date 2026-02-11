newIsland(char *X,char *Y,int i,int j,int d) {
    Island *p; Fragment *f,**ff,*L; int k,ii,jj,iii,jjj,l; double s;

    p=newBlock(sizeof(Island));

    ii=i; jj=j; l=0; s=0.;

    if(d>0) {
        ff=&L;
        for(;;) {
            s+=GS[(int)X[ii]][(int)Y[jj]];
            if(++l==1) {iii=ii; jjj=jj;}
            k=U[ii][jj].up;
            if(k) {
                f=newBlock(sizeof(Fragment));
                f->beginX=iii; f->beginY=jjj; f->length=l;
                l=0; *ff=f; ff=&f->next;
            }
            if(k==NOWHERE) break;
            ii++; jj++; if(k>=0) ii+=k; else jj-=k;
        }
        *ff=NULL;
        p->beginX= i; p->beginY= j;
        p->endX  =ii; p->endY  =jj;
    } else {
        L=NULL;
        for(;;) {
            s+=GS[(int)X[ii]][(int)Y[jj]];
            if(++l==1) {iii=ii; jjj=jj;}
            k=U[ii][jj].down;
            if(k) {
                f=newBlock(sizeof(Fragment));
                f->beginX=iii-l+1; f->beginY=jjj-l+1; f->length=l;
                l=0; f->next=L; L=f;
            }
            if(k==NOWHERE) break;
            ii--; jj--; if(k>=0) ii-=k; else jj+=k;
        }
        p->beginX=ii; p->beginY=jj;
        p->endX  = i; p->endY  = j;
    }

    p->fragments=L;

    p->score=s+GapC*expectedScore;

    return(p);
}
