hsc_cleanup(void) {

    if (ht!=NULL) free(ht),ht=NULL;
    if (fc!=NULL) free(fc),fc=NULL;
    if (fa!=NULL) free(fa),fa=NULL;
    if (ft!=NULL) free(ft),ft=NULL;
    if (fe!=NULL) free(fe),fe=NULL;
    if (nb!=NULL) free(nb),nb=NULL;
    if (hp!=NULL) free(hp),hp=NULL;
    if (elp!=NULL) free(elp),elp=NULL;
    if (eln!=NULL) free(eln),eln=NULL;
    if (cl!=NULL) free(cl),cl=NULL;
    if (cc!=NULL) free(cc),cc=NULL;
    if (rfm!=NULL) free(rfm),rfm=NULL;
    if (con!=NULL) free(con),con=NULL;
}
