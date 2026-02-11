rowCount ( const QModelIndex & parent ) const
{
	if(parent!=QModelIndex())
		return 0;

	return n_rows;
}
