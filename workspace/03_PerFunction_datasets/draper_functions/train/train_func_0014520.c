victoire(){
	jeu_en_cours=false;
	emit bloque_module( true );
	emit plaqueReglable( true );
	reinit_plaques_tirage( false );
	affiche_solutions();
	horloge->arrete();
	pbAlea->setEnabled( true );
	pbJouer->setEnabled( true );

	if(!trop_tard){
		renard_apres_jeu(true);
	}
}
