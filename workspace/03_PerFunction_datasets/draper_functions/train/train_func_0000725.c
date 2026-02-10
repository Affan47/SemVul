JAXeventnow(Jax *jax)
{
	if(JAXeventsqueued(jax))
	{
		XNextEvent(jax->d, &jax->xe);
		switch(jax->xe.type)
		{
			case MappingNotify:
				XRefreshKeyboardMapping((XMappingEvent*)&jax->xe);
				jax->xe.type=0;
				break;
			default:
				if (jax->EH)
					jax->EH(jax);
				break;
		}
	}
	return(0);
}
