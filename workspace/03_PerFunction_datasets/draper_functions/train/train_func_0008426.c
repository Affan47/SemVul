HasPath( string path ) const{
	standardizePathString( path );
	for( uint32 i = 0; i < m_pathList.size(); ++i ){
		if( m_pathList[i] == path )
			return true;
	}
	return false;
}
