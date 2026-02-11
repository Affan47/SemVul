buttonpressed(int         id)
{
    tdialogbox::buttonpressed(id);
    switch (id) {

    case 1:
    case 2:
        action = id;
        break;


    case 4: {
        if ( ( sel1 != 255) && ( sel2 != sel1 ) && ( sel2 != 255 ) && ( sel1 != 8) && ( sel2 != 8 ) ) {
            actmap->player[sel1].swap ( actmap->player[sel2] );
            anzeige();
        }
    }
    break;
    case 5: {
        if ( ( sel1 != 255) && ( sel2 != sel1 ) && ( sel2 != 255 ) ) {


            if ( sel1 != 8 )
                for ( Player::VehicleList::iterator i = actmap->player[sel2].vehicleList.begin(); i != actmap->player[sel2].vehicleList.end(); ) {
                    (*i)->color = sel1*8;
                    actmap->player[sel1].vehicleList.push_back ( *i );
                    i = actmap->player[sel2].vehicleList.erase( i );
                }

            Player::BuildingList bl = actmap->player[sel2].buildingList;
            for ( Player::BuildingList::iterator i = bl.begin(); i != bl.end(); ++i)
                (*i)->convert( sel1 );

            for (int i =0; i < actmap->xsize * actmap->ysize ; i++ ) {
                MapField* fld = &actmap->field[i];
                for ( MapField::MineContainer::iterator i = fld->mines.begin(); i != fld->mines.end(); i++ )
                    if ( i->player == sel2 && sel1 != 8)
                        i->player = sel1;

            }
            anzeige();
        }
    }
    break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        if ( id-6 != sel1 ) {
            sel2 = sel1;
            sel1 = id-6;
            anzeige();
        }
        break;
    }
}
