create_pressure_quant(b_id)
body_id b_id;
{
  if ( web.pressure_flag )
  {
    int gq = get_body_volquant(b_id);
    int mc = GEN_QUANT(gq)->method_count;
    char *volsum = temp_calloc(40,mc);
    char *formula = temp_calloc(2,40*mc + 100);
    char qname[1000];
    int q,i,j;

    sprintf(qname,"body_%d_ambient_energy",ordinal(b_id)+1);
    q = find_quantity(qname);
    if ( q < 0 ) q = new_quantity(qname,Q_INFO);
    set_body_ambquant(b_id,q);
    GEN_QUANT(q)->flags |= DEFAULT_QUANTITY;
    sprintf(volsum,"body[%d].volconst",ordinal(b_id)+1);
    for ( j = 0 ; j < mc ; j++ )
    { int m = GEN_QUANT(gq)->meth_inst[j];
      struct method_instance *mi = METH_INSTANCE(m);
      strcat(volsum,((mi->modulus > 0.0) ? "+" : "+"));
      strcat(volsum,mi->name);
      strcat(volsum,".value");
      mi->flags |= Q_COMPOUND;
    }
    GEN_QUANT(q)->method_count = 0;
    i = ordinal(b_id)+1;
    sprintf(formula,"-ambient_pressure_value*(body[%d].target*(log(%s)-log(body[%d].target))-(%s-body[%d].target))",
       i,volsum,i,volsum,i);
    cmdptr = formula;
    exparse(0,&(GEN_QUANT(q)->expr),USERCOPY);
    sprintf(msg,"%s formula",qname);
    strncpy(GEN_QUANT(q)->expr.name,msg,EXPNAMESIZE-1);
    cmdptr = NULL;
    GEN_QUANT(q)->flags |= Q_COMPOUND;
    GEN_QUANT(q)->next_compound = compound_quant_list_head;
    compound_quant_list_head = q;
    if ( get_battr(b_id) & FIXEDVOL )
       GEN_QUANT(q)->flags |= Q_ENERGY;
    else   GEN_QUANT(q)->flags |= Q_INFO;
    GEN_QUANT(gq)->flags &= ~Q_FIXED;
    GEN_QUANT(gq)->flags |= Q_INFO;
    temp_free(volsum);
    temp_free(formula);
  }
}
