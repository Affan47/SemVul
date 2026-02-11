normalizeBaseFreqs(
                        double *F,double fT,double fC,double fA,double fG
                        ) {
    double s;

    s=fT+fC+fA+fG;

    if(s<REAL_MIN) {fT=1.; fC=1.; fA=1.; fG=1.; s=4.;}

    fT/=s; fC/=s; fA/=s; fG/=s;

    if(fT<ATOLPARAM) fT=ATOLPARAM;
    if(fC<ATOLPARAM) fC=ATOLPARAM;
    if(fA<ATOLPARAM) fA=ATOLPARAM;
    if(fG<ATOLPARAM) fG=ATOLPARAM;

    F[T]=fT; F[C]=fC; F[A]=fA; F[G]=fG;

}
