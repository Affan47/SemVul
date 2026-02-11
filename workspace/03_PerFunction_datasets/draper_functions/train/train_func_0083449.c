print_dset_dtype_meta(const iter_t *iter)
{
    unsigned long total;
    size_t   dtype_size;
    unsigned u;

    if(iter->dset_ntypes) {
        printf("Dataset datatype information:\n");
        printf("\t# of unique datatypes used by datasets: %lu\n", iter->dset_ntypes);
        total = 0;
        for(u = 0; u < iter->dset_ntypes; u++) {
            H5Tencode(iter->dset_type_info[u].tid, NULL, &dtype_size);
            printf("\tDataset datatype #%u:\n", u);
            printf("\t\tCount (total/named) = (%lu/%lu)\n",
                    iter->dset_type_info[u].count, iter->dset_type_info[u].named);
            printf("\t\tSize (desc./elmt) = (%lu/%lu)\n", (unsigned long)dtype_size,
                    (unsigned long)H5Tget_size(iter->dset_type_info[u].tid));
            H5Tclose(iter->dset_type_info[u].tid);
            total += iter->dset_type_info[u].count;
        }
        printf("\tTotal dataset datatype count: %lu\n", total);
    }

    return 0;
}
