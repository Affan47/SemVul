freeSpeciesConcatenateList(speciesConcatenateList scl){
    while (scl) {
        speciesConcatenateList next = scl->next;
        free(scl->species_name);
        delete scl;
        scl = next;
    }
}
