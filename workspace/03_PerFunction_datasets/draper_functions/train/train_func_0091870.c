resoudre() {
	if(jeu_en_cours){
		emit bloque_module( true );
		emit plaqueReglable( true );
		reinit_plaques_tirage( false );
		pbJouer->setEnabled( true );
		horloge->arrete();
		defaite();
		jeu_en_cours=false;
		affiche_solutions();
	} else {
		lancement_calcul();
	}
}
