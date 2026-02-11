readPolygon()
{
	int numRings = dis.readInt();

#if DEBUG_WKB_READER
	cout<<"WKB numRings: "<<numRings<<endl;
#endif

        LinearRing *shell = NULL;
        if( numRings > 0 )
            shell = readLinearRing();

	vector<Geometry *>*holes=NULL;
	if ( numRings > 1 )
	{
		try {
			holes = new vector<Geometry *>(numRings-1);
			for (int i=0; i<numRings-1; i++)
				(*holes)[i] = (Geometry *)readLinearRing();
		} catch (...) {
			for (unsigned int i=0; i<holes->size(); i++)
				delete (*holes)[i];
			delete holes;
			delete shell;
			throw;
		}
	}
	return factory.createPolygon(shell, holes);
}
