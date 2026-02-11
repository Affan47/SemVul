find_planes(void)
    {
      unsigned int i, j;
      SYMMETRY_ELEMENT * plane ;

      plane = init_ultimate_plane() ;
      if( plane != NULL ){
        MolecularPlane = plane ;
        PlanesCount++ ;
        Planes = (SYMMETRY_ELEMENT **) realloc( Planes, sizeof( SYMMETRY_ELEMENT* ) * PlanesCount ) ;
        if( Planes == NULL ){
          perror( "Out of memory in find_planes" ) ;
          exit( EXIT_FAILURE ) ;
        }
        Planes[ PlanesCount - 1 ] = plane ;
      }
      for( i = 1 ; i < _mol->NumAtoms() ; i++ ){
        for( j = 0 ; j < i ; j++ ){
          if( !equivalentAtoms(*_mol->GetAtom(i+1), *_mol->GetAtom(j+1)) )
            continue ;
          if( ( plane = init_mirror_plane( i, j ) ) != NULL ){
            PlanesCount++ ;
            Planes = (SYMMETRY_ELEMENT **) realloc( Planes, sizeof( SYMMETRY_ELEMENT* ) * PlanesCount ) ;
            if( Planes == NULL ){
              perror( "Out of memory in find_planes" ) ;
              exit( EXIT_FAILURE ) ;
            }
            Planes[ PlanesCount - 1 ] = plane ;
          }
        }
      }
    }
