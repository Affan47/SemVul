onEntranceClick ( PG_MessageObject* obj, const SDL_MouseButtonEvent* event, int entranceNum ) {
            if ( vt ) {
               PG_Widget* swi = FindChild( "single_weapon_info", true );
               if ( swi ) {
                  ContainerBaseType::TransportationIO tio = vt->entranceSystems[entranceNum];
                  setWidgetTransparency( "pad_transport_in",      tio.mode & ContainerBaseType::TransportationIO::In      ? 0 : 255 );
                  setWidgetTransparency( "pad_transport_out",     tio.mode & ContainerBaseType::TransportationIO::Out     ? 0 : 255 );
                  setWidgetTransparency( "pad_transport_docking", tio.mode & ContainerBaseType::TransportationIO::Docking ? 0 : 255 );

                  for ( int i = 0; i < cmovemalitypenum; ++i )
                     if ( (vt->vehicleCategoriesStorable & (1<<i)) && (tio.vehicleCategoriesLoadable & (1<<i)))
                        setImage( ASCString("unitpad_transport_") + unitCategoryTags[i], IconRepository::getIcon("pad_symbol_ok.png") );
                     else
                        setImage( ASCString("unitpad_transport_") + unitCategoryTags[i], IconRepository::getIcon("pad_symbol_no.png") );

                  ASCString s;
                  for ( int i = 0; i < ContainerBaseType::functionNum; ++i )
                     if ( tio.requiresUnitFeature.test( i )) {
                        if ( s.length() )
                           s += ", ";
                        s += ContainerBaseType::getFunctionName( ContainerBaseType::ContainerFunctions(i));
                     }
                  setLabelText( "unitpad_transport_specialfunctions", s );

                  setLabelText( "unitpad_transport_attackafterwards", tio.disableAttack ? "no" : "yes" );

                  entranceHeights.clear();
                  for ( int i = 0; i < 8; ++i )
                     if ( vt->height & (1 << i) & tio.container_height )
                        for ( int j = 0; j < 8; ++j )
                           if ( !tio.height_abs || tio.height_abs & (1 <<j ))
                              if ( tio.height_rel == -100 || getheightdelta( i, j ) == tio.height_rel  )
                                 entranceHeights.push_back( make_pair(i,j));

                  PG_Widget* w = FindChild( "unitpad_transport_leveldisplay", true );
                  if ( w )
                     w->Update();
               }

               for ( int i = 0; i < vt->entranceSystems.size(); ++i ) {
                  ASCString n = "pad_transport_square" + ASCString::toString(i);
                  PG_Widget* w = FindChild( n, true );
                  if ( w ) {
                     if ( i == entranceNum )
                        w->SetTransparency( 0 );

                     else
                        w->SetTransparency( 255 );


                  }
               }
               Update();
            }
            return true;
         }
