isGlobal()
{
	if( _type == ResourceModel::RE_GLOB_NOPRESERVABLE || _type == ResourceModel::RE_LOC_PRESERVABLE )
		return true;

	return false;
}
