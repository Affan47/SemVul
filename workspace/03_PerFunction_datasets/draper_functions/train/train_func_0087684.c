calculate_lambda ( const double** mat_b, int alpha_size,
                          double* p, double* q )
{
  double **JP;
  int k;
  double *root_location;
  int N_root;
  Lambda Lambda_local;

  Alphsize = alpha_size;

  if( ! Check_range( mat_b ) ) return -1.0;

  root_location = Locate_det_zero(mat_b, &N_root);
  if( root_location == NULL && N_root > 0 ) return -1.0;


  JP = dmatrix(1,Alphsize,1,Alphsize);

  if (N_root == 0){
    Lambda_local = Find_JP(mat_b, 0, Lambda_UB, JP, p, q);
    if (1 == Lambda_local.flag) {


      free( root_location );
      free_dmatrix( JP, 1, Alphsize, 1, Alphsize );
      return (Lambda_local.min + Lambda_local.max) / 2.0;
    }
    else if (-1 == Lambda_local.flag) {

    }
  }
  else if (N_root > 0) {


    for (k=0; k<= N_root; k++){
      if (k==0) {Lambda_local.min =0; Lambda_local.max = root_location[0];}
      else if (k== N_root) {Lambda_local.min = root_location[N_root-1]; Lambda_local.max = Lambda_UB+Epsilon;}
      else {Lambda_local.min = root_location[k-1]; Lambda_local.max = root_location[k]; }
      Lambda_local = Find_JP(mat_b, Lambda_local.min, Lambda_local.max, JP, p, q);
      if (1 == Lambda_local.flag) {


	free( root_location );
      free_dmatrix( JP, 1, Alphsize, 1, Alphsize );
	return (Lambda_local.min + Lambda_local.max) / 2.0;
      }
      else if (-1 == Lambda_local.flag) {

      }
    }
  }


  free( root_location );
  free_dmatrix( JP, 1, Alphsize, 1, Alphsize );
  return -1.0;
}
