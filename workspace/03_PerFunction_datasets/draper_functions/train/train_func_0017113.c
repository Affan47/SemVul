zCheckDNAForCurrentStopCodon(zDNA* dna, coor_t pos){
	if((zGetDNAS5(dna,pos) == 3) &&
	   (((zGetDNAS5(dna,pos+1) == 0) &&
		 ((zGetDNAS5(dna,pos+2) == 0) ||
		  (zGetDNAS5(dna,pos+2) == 2))) ||
		((zGetDNAS5(dna,pos+1) == 2) &&
		 (zGetDNAS5(dna,pos+2) == 0)))){
		return true;
	}
	return false;
}
