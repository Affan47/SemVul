element_mod_n(Matrix& Mat,double n)
{


  double tmp;
  for( int j=1;j<=Mat.Ncols();j++){
    for( int i=1;i<=Mat.Nrows();i++){

      while( !( (Mat(i,j)>0) && (Mat(i,j)<n) ) ){
	tmp = ( Mat(i,j) - rounddouble(Mat(i,j)/n)*n );
	Mat(i,j)= tmp > 0 ? tmp : tmp + n;
      }

    }

  }

}
