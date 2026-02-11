WriteJsdFile(PDBChain *chain, char *filename)
{

  FILE *fp = fopen(filename, "w");
  if (!fp) {
    fprintf(stderr, "Unable to open JSD file %s\n", filename);
    return 0;
  }


  for (int i = 0; i < chain->NResidues(); i++) {
    PDBResidue *residue = chain->Residue(i);


    PDBAminoAcid *amino_acid = residue->AminoAcid();
    char letter = (amino_acid) ? amino_acid->Letter() : '-';


    fprintf(fp, "%-7d %c %13.5f 0/0\n", i, letter, residue->conservation);
  }


  fclose(fp);


  return chain->NResidues();
}
