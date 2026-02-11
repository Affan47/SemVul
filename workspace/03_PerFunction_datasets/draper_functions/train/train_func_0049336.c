uniqueEmptyProductions()
{
	if ( addUniqueEmptyProductions ) {
		int limit = prodList.length();
		for ( DefList::Iter prod = prodList; prod.lte(); prod++ ) {
			if ( prod->prodId == limit )
				break;


			char name[20];
			sprintf(name, "U%li", prodList.length());
			KlangEl *prodName = getKlangEl( this, name, KlangEl::NonTerm );
			Definition *newDef = new Definition( InputLoc(), prodName,
					0 ,
					false, 0, 0, 0, prodList.length(), Definition::Production );
			prodName->defList.append( newDef );
			prodList.append( newDef );

			prod->uniqueEmptyLeader = prodName;
		}
	}
}
