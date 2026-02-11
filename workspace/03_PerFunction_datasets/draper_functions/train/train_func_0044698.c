CodonSubmat_add_nucleic(CodonSubmat *cs, Submat *nucleic){
    register gint a, b, c, d, e, f, codon_a, codon_b;
    register gchar *alphabet = "ACGTN";
    register gint score;
    for(a = 0; a < 5; a++){
        for(b = 0; b < 5; b++){
            for(c = 0; c < 5; c++){
                for(d = 0; d < 5; d++){
                    for(e = 0; e < 5; e++){
                        for(f = 0; f < 5; f++){
                            score = Submat_lookup(nucleic, alphabet[a],
                                                           alphabet[d])
                                  + Submat_lookup(nucleic, alphabet[b],
                                                           alphabet[e])
                                  + Submat_lookup(nucleic, alphabet[c],
                                                           alphabet[f]);
                            codon_a = cs->codon_index[a][b][c];
                            codon_b = cs->codon_index[d][e][f];
                            cs->codon_submat[codon_a][codon_b] /= 2;
                            cs->codon_submat[codon_a][codon_b] += score;
                            }
                        }
                    }
                }
            }
        }
    return;
    }
