bcf1_sync_alleles(bcf1_t *line, kstring_t *str)
{

    int i;
    for (i=0; i<line->n_allele; i++)
        bcf_enc_vchar(str, strlen(line->d.allele[i]), line->d.allele[i]);
}
