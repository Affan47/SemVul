force_project(fin,v_id,fout)
REAL *fin;
vertex_id v_id;
REAL *fout;
{ int attr = get_vattr(v_id);
  int i,j;
  if ( attr & CONSTRAINT )
  { conmap_t * conmap = get_v_constraint_map(v_id);
    int oncount = 0;
    struct constraint *con[MAXCONPER];
    int conlist[MAXCONPER];
    REAL perp[MAXCOORD];

    for ( j = 1 ; j <= (int)conmap[0] ; j++ )
    { if ( conmap[j] & CON_HIT_BIT )
      { conlist[oncount] = conmap[j] & CONMASK;
        con[oncount] = get_constraint(conmap[j]);
        oncount++;
      }
      if ( oncount )
      { constr_proj(TANGPROJ,oncount,con,get_coord(v_id),
                                 fin,perp,conlist,0,v_id);
        for ( j = 0 ; j < SDIM ; j++ )
          fout[j] = fin[j] - perp[j];
        return;
      }
    }
  }
  else if ( attr & BOUNDARY )
  { MAT2D(a,MAXCOORD,MAXCOORD);
    b_proj(get_boundary(v_id),get_param(v_id),a,TANGPROJ,v_id);
    matvec_mul(a,fin,fout,SDIM,SDIM);
    return;
  }


  for ( i = 0 ; i < SDIM ; i++ )
    fout[i] = fin[i];
}
