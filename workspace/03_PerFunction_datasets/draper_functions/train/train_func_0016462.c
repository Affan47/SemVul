vl_aib_merge_nodes (VlAIB * aib, vl_uint i, vl_uint j, vl_uint new)
{
  vl_uint last_entry = aib->nentries - 1 ;
  vl_uint c, n ;


  aib->nwhich = 0;


  if(i > j) { vl_uint tmp = j; j = i; i = tmp; }


  aib-> Px   [i] += aib->Px[j] ;
  aib-> beta [i]  = BETA_MAX ;
  aib-> nodes[i]  = new ;

  for (c = 0; c < aib->nlabels; c++)
    aib-> Pcx [i*aib->nlabels + c] += aib-> Pcx [j*aib->nlabels + c] ;


  aib-> Px    [j]  = aib-> Px    [last_entry];
  aib-> beta  [j]  = aib-> beta  [last_entry];
  aib-> bidx  [j]  = aib-> bidx  [last_entry];
  aib-> nodes [j]  = aib-> nodes [last_entry];

  for (c = 0 ;  c < aib->nlabels ; c++)
    aib-> Pcx[j*aib->nlabels + c] = aib-> Pcx [last_entry*aib->nlabels + c] ;


  aib-> nentries -- ;


  for (n = 0 ; n < aib->nentries; n++) {
    if(aib->bidx[n] == i || aib->bidx[n] == j) {
        aib->bidx  [n] = 0;
        aib->beta  [n] = BETA_MAX;
        aib->which [aib->nwhich++] = n ;
      }
    else if(aib->bidx[n] == last_entry) {
      aib->bidx[n] = j ;
    }
  }
}
