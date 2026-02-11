chk_modsym(struct sy_t *syp)
{
 switch ((byte) syp->sytyp) {

  case SYM_N:
   if (__cur_declobj == MODULE) chk_1wire(syp->el.enp);
   else chk_1reg(syp->el.enp);
   break;
  case SYM_TSK: case SYM_F: case SYM_STSK: case SYM_SF:
   if (!syp->sydecl)
    __gferr(770, syp->syfnam_ind, syp->sylin_cnt,
     "%s %s not declared", __to_sytyp(__xs, syp->sytyp), syp->synam);
   break;

  case SYM_CA: case SYM_TCHK: case SYM_PTH: break;


  case SYM_I: case SYM_LB: case SYM_UDP: case SYM_PRIM:
  break;
 default:

  __misc_gfterr(__FILE__, __LINE__, syp->syfnam_ind, syp->sylin_cnt);
 }
}
