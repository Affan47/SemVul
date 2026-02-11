mltmod(const FourByteLong a, const FourByteLong s, const FourByteLong m)


{
#define h 32768L
static FourByteLong mltmod,a0,a1,k,p,q,qh,rh;


    if((a <= 0 || a >= m || s <= 0 || s >= m)) {
     char errmsg[300];
    fputs(" a, m, s out of order in mltmod - ABORT!",stderr);

    sprintf(errmsg, "BUG: a, s, m out of order in mltmod - ABORT! \n"  \
    " a = %12ld s = %12ld m = %12ld sizeof(FourByteLong)= %d\n"  \
    " ERROR in mltmod :  mltmod requires: 0 < a < m; 0 < s < m", \
    (long) a, (long) s, (long) m, (int) sizeof mltmod);
    stop(errmsg);
    }

    if(!(a < h)) goto S20;
    a0 = a;
    p = 0;
    goto S120;
S20:
    a1 = a/h;
    a0 = a-h*a1;
    qh = m/h;
    rh = m-h*qh;
    if(!(a1 >= h)) goto S50;
    a1 -= h;
    k = s/qh;
    p = h*(s-k*qh)-k*rh;
S30:
    if(!(p < 0)) goto S40;
    p += m;
    goto S30;
S40:
    goto S60;
S50:
    p = 0;
S60:


    if(!(a1 != 0)) goto S90;
    q = m/a1;
    k = s/q;
    p -= (k*(m-a1*q));
    if(p > 0) p -= m;
    p += (a1*(s-k*q));
S70:
    if(!(p < 0)) goto S80;
    p += m;
    goto S70;
S90:
S80:
    k = p/qh;


    p = h*(p-k*qh)-k*rh;
S100:
    if(!(p < 0)) goto S110;
    p += m;
    goto S100;
S120:
S110:
    if(!(a0 != 0)) goto S150;


    q = m/a0;
    k = s/q;
    p -= (k*(m-a0*q));
    if(p > 0) p -= m;
    p += (a0*(s-k*q));
S130:
    if(!(p < 0)) goto S140;
    p += m;
    goto S130;
S150:
S140:
    mltmod = p;
    return mltmod;
#undef h
}
