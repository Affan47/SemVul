storeIslandActivationState(btCollisionWorld* colWorld)
{

	{


		int index = 0;
		int i;
		for (i=0;i<colWorld->getCollisionObjectArray().size();i++)
		{
			btCollisionObject* collisionObject= colWorld->getCollisionObjectArray()[i];
			if (!collisionObject->isStaticOrKinematicObject())
			{
				collisionObject->setIslandTag( m_unionFind.find(index) );
				collisionObject->setCompanionId(-1);
			} else
			{
				collisionObject->setIslandTag(-1);
				collisionObject->setCompanionId(-2);
			}
			index++;
		}
	}
}
