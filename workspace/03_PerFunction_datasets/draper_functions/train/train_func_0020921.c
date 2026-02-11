detach()
{
	if ( active )
	{
		active = false;

		btDynWorld->removeConstraint(constraint);
		delete constraint;
		pickedBody->forceActivationState(ACTIVE_TAG);
		pickedBody->setDeactivationTime( 0.001 );


		*pickedBool = false;
	}
}
