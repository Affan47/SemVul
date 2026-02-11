addUnit( int pos , int race , int level , int nb )
{
	GenericFightUnit * uni =getUnit( pos );

		if( nb != 0 ){
			if( !uni ){
				uni = new GenericFightUnit();
			}

			uni->setCreature( race, level );
			uni->setNumber( nb );
		}	else {
			if( uni ) {
				uni->setNumber( nb );
				delete uni;
				uni = NULL;
			}
		}
		setUnit( pos, uni );
}
