init() {
    int i;
    for (i=1; i<HR_NTYPES; i++) {
        rac_per_class[i] = (double*) calloc(hr_nclasses[i], sizeof(double));
        max_slots[i] = (int*) calloc(hr_nclasses[i], sizeof(int));
        cur_slots[i] = (int*) calloc(hr_nclasses[i], sizeof(int));
    }
}
