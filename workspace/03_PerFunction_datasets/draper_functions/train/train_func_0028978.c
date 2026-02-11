knot_energy_hessian(v_info)
struct qinfo *v_info;
{
  REAL *x = get_coord(v_info->id);
  REAL energy = 0.0;
  vertex_id w_id;
  int i,j;
  REAL d[MAXCOORD];
  REAL rr,p,fact;
  MAT2D(hessvw,MAXCOORD,MAXCOORD);
  MAT2D(hessvv,MAXCOORD,MAXCOORD);
  REAL modulus;
  REAL vcharge = charge_attr >= 0 ?
        *((REAL*)get_extra(v_info->id,charge_attr)) : 1.;

  modulus = METH_INSTANCE(v_info->method)->modulus
                  *GEN_QUANT(METH_INSTANCE(v_info->method)->quant)->modulus;


  for(i=0;i<SDIM;i++) for(j=0;j<SDIM;j++) hessvv[i][j]=0.;

  FOR_ALL_VERTICES(w_id)
  { REAL *y = get_coord(w_id);
    REAL charges;
    if ( equal_id(v_info->id,w_id) ) continue;
    charges = charge_attr >= 0 ?
              *((REAL*)get_extra(w_id,charge_attr))*vcharge : 1.;
    for ( i = 0 ; i < SDIM ; i++ ) d[i] = x[i] - y[i];
    rr = SDIM_dot(d,d);
    ke_pow(rr,p);
    energy += charges/p;
    fact = 2*ke_power/(p*rr);
    for ( i = 0 ; i < SDIM ; i++ )
      v_info->grad[0][i] -= 2*charges*fact*d[i];
    for ( i=0; i<SDIM; i++ )
      for ( j=0; j<SDIM; j++ )
      {
        register REAL hessij = fact*((2*ke_power+2)/rr * d[i]*d[j] - (i==j));
        hessij *= modulus*charges;
        hessvw[i][j] = - hessij;
        hessvv[i][j] += 2*hessij;
      }
    fill_mixed_entry(v_info->S, v_info->id, w_id, hessvw);
  }
  fill_self_entry(v_info->S, v_info->id, hessvv);
  return modulus*energy;
}
