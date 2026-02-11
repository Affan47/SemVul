deleteCampaign()
{
	TRACE("Engine::deleteCampaign");

	if( _campaign ) {
		delete _campaign;
		_campaign = NULL;
	}
}
