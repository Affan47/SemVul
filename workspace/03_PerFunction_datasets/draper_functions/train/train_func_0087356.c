local_calc_leftside()
{ vertex_id v_id;
  int bi,bj;


  if ( !approx_curve_flag )
    FOR_ALL_VERTICES(v_id)
    {
      volgrad *vgptri,*vgptrj;
      ATTR attr = get_vattr(v_id);

      if ( attr & FIXED ) continue;

      for ( vgptri = get_vertex_vgrad(v_id); vgptri ; vgptri = vgptri->chain )
      { REAL tmp;
        bi = vgptri->fixnum;
        if ( (bi < 0) || (bi >= fixcount) ) continue;
        degfree++;
        tmp = SDIM_dot(vgptri->velocity,vgptri->grad);


        { if ( sparse_constraints_flag )
          { sp_hash_search(&LS,bi,bi,tmp); }
          else
            rleftside[bi][bi] += tmp;
        }
        for ( vgptrj = vgptri->chain ; vgptrj ; vgptrj = vgptrj->chain )
        { tmp = SDIM_dot(vgptri->grad,vgptrj->velocity);
          bj = vgptrj->fixnum;
          if ( (bj < 0) || (bj >= fixcount) ) continue;

          {
            if ( sparse_constraints_flag )
            { if ( bi < bj ) sp_hash_search(&LS,bi,bj,tmp);
              else sp_hash_search(&LS,bj,bi,tmp);
            }
            else
            { rleftside[bi][bj] += tmp;
              rleftside[bj][bi] += tmp;
            }
          }
        }
      }
    }
}
