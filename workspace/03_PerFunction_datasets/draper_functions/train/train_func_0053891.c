fill_ld_handle(struct h_t *hp, struct hrec_t *hrp,
 struct net_pin_t *npp)
{
 struct itree_t *itp2;
 struct gate_t *gp;

 hp->hin_itp = __inst_ptr;
 switch ((byte) npp->npntyp) {
  case NP_ICONN: case NP_BIDICONN: case NP_PB_ICONN:

   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   itp2 = &(__inst_ptr->in_its[npp->elnpp.eii]);
   hp->hin_itp = itp2;
   break;
  case NP_MDPRT: case NP_BIDMDPRT: case NP_PB_MDPRT:

   hrp->htyp = vpiPort;
   hrp->hu.hpi = npp->obnum;
   break;
  case NP_CONTA:
   hrp->htyp = vpiContAssign;
   hrp->hu.hcap = npp->elnpp.ecap;
   break;
  case NP_GATE: case NP_TRANIF: case NP_TRAN:
   gp = npp->elnpp.egp;
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
    {
     hrp->htyp = vpiContAssign;
     hrp->htyp2 = vpiGate;
     hrp->hu.hgp = gp;
    }
   else
    {
     gp = npp->elnpp.egp;
     hrp->htyp = vpiPrimTerm;
     hrp->hu.hgp = gp;
     hrp->hi = npp->obnum;
    }
   break;
  default: return(FALSE);
 }
 return(TRUE);
}
