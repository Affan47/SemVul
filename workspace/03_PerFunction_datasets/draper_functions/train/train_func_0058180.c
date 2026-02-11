find_higher_axes(void)
    {
      unsigned int i, j, k;
      SYMMETRY_ELEMENT * axis ;

      for( i = 0 ; i < _mol->NumAtoms() ; i++ ){
        for( j = i + 1 ; j < _mol->NumAtoms() ; j++ ){
          if( !equivalentAtoms(*_mol->GetAtom(i+1), *_mol->GetAtom(j+1)) )
            continue ;
          if( fabs( DistanceFromCenter[i] - DistanceFromCenter[j] ) > TolerancePrimary )
            continue ;
          for( k = 0 ; k < _mol->NumAtoms() ; k++ ){
            if( !equivalentAtoms(*_mol->GetAtom(i+1), *_mol->GetAtom(k+1)) )
              continue ;
            if( ( fabs( DistanceFromCenter[i] - DistanceFromCenter[k] ) > TolerancePrimary ) ||
                ( fabs( DistanceFromCenter[j] - DistanceFromCenter[k] ) > TolerancePrimary ) )
              continue ;
            if( ( axis = init_higher_axis( i, j, k ) ) != NULL ){
              NormalAxesCount++ ;
              NormalAxes = (SYMMETRY_ELEMENT **) realloc( NormalAxes, sizeof( SYMMETRY_ELEMENT* ) * NormalAxesCount ) ;
              if( NormalAxes == NULL ){
                perror( "Out of memory in find_higher_axes" ) ;
                return;
              }
              NormalAxes[ NormalAxesCount - 1 ] = axis ;
            }
          }
        }
      }
    }
