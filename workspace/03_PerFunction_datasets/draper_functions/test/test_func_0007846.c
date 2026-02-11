combinaisons(const calcul& A, const calcul& B){

	ajouteBase(A+B);

	if(A.valeur_calcul<B.valeur_calcul) {
		ajouteBase(B-A);
	}
	else if(A.valeur_calcul>B.valeur_calcul) {
		ajouteBase(A-B);
	}

	if(A.valeur_calcul!=1 && B.valeur_calcul!=1) {
		ajouteBase(A*B);

		if(A.valeur_calcul==B.valeur_calcul) {
			calcul C=A/B; calcul D=B/A;
			if(C < D) {
				ajouteBase(C);
			} else {
				ajouteBase(D);
			}
		}
		else {
			if (A.valeur_calcul % B.valeur_calcul==0){
				ajouteBase(A/B);
			}
			else if (B.valeur_calcul % A.valeur_calcul==0){
				ajouteBase(B/A);
			}
		}
	}
}
