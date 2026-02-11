getExperience( GenericLord * lord )
{

	uint ret = 0;

	if( lord == _attackLord ) {
		ret = _attackExp;
	} else if( lord == _defendLord ) {
		ret = _defendExp;
	}

	return ret;
}
