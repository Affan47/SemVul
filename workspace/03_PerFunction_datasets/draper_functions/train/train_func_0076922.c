adns_forallqueries_begin(adns_state ads) {
  adns__consistency(ads,0,cc_entex);
  ads->forallnext=
    ads->udpw.head ? ads->udpw.head :
    ads->tcpw.head ? ads->tcpw.head :
    ads->childw.head ? ads->childw.head :
    ads->output.head;
}
