tous_les_tirages(){

	set<tirage> resultat;

	list<pseudo_tirage> liste_pseudo=cree_liste_pseudo();
	list<pseudo_tirage>::iterator PT;

	for(PT=liste_pseudo.begin();PT!=liste_pseudo.end();PT++){
		resultat.insert(pseudo_en_tirage(*PT));
	}

	return resultat;
}
