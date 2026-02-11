ap_texpr0_binop(ap_texpr_op_t op, ap_texpr0_t* opA, ap_texpr0_t* opB, ap_texpr_rtype_t type, ap_texpr_rdir_t dir)
{
  if (!ap_texpr_is_binop(op)){
    fprintf(stderr,"ap_texpr0.c: ap_texpr0_binop: binary operator expected\n");
    abort();
  }
  return ap_texpr0_node(op,type,dir,opA,opB);
}
