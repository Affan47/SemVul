count_species() {
        awte_assert(!in_single_mode());
        if (species_count == size_t(-1)) {
            species_count = 0;
            for (GBDATA *gb_species = find_first(gb_main); gb_species; gb_species = find_next(gb_species)) {
                species_count++;
            }
        }
        return species_count;
    }
