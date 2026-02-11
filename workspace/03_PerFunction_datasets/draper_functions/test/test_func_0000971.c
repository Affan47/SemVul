check_matrix(int postcon, int precon)
{
     if ( postcon == -1 || precon == -1 )
       return DEFAULT_C_WEIGHT;

     return ((int)rensetu_mtr[ rensetu_tbl[postcon].i_pos * J_NUM
			       + rensetu_tbl[precon].j_pos ]);
}
