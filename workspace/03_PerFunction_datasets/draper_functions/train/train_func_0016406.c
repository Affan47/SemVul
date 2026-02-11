numXLoci(GList<GXLocus>& xloci, int& last_id) {
  for (int l=0;l<xloci.Count();l++) {
    if (xloci[l]->qloci.Count()==0) continue;
    last_id++;
    xloci[l]->id=last_id;
    }
}
