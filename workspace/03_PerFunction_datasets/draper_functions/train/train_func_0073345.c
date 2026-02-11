vectorize_velosig(lofig_list *f)
{
ptype_list *p;
velosig *vs, *vv=NULL;
chain_list *ch;

   p=getptype(f->USER, VEL_SIG);
   for (vs=(velosig *)p->DATA;vs;vs=vs->NEXT) {
      if (vv && vv->NAME==vs->NAME && abs(vv->RIGHT-vs->RIGHT)==1 ) {
         vv->RIGHT=vs->RIGHT;
         vv->VSIG=addchain(vv->VSIG, vs);
         vs->TYPE='V';
         vs->SUPER=vv;
      } else {
         if (vv) {
            if (vs->NAME==vv->NAME) {

               for (ch=vv->VSIG; ch; ch=ch->NEXT)
                  ((velosig *)ch->DATA)->TYPE=vv->TYPE;
            } else
               vv->VSIG=(chain_list *)reverse(vv->VSIG);
            vv=NULL;
         }
         if (vs->LEFT!=-1) {
            vv=dupvelosig(p, vs);
            vv->VSIG=addchain(vv->VSIG, vs);
            vs->TYPE='V';
            vs->SUPER=vv;
         }
      }
   }
   if (vv)
      vv->VSIG=(chain_list *)reverse(vv->VSIG);
}
