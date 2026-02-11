animateJoints(bool CalculateAbsolutePositions)
{
	checkJoints();

	if (Mesh && Mesh->getMeshType() == EAMT_SKINNED )
	{
		if (JointsUsed)
		{
			f32 frame = getFrameNr();

			CSkinnedMesh* skinnedMesh=reinterpret_cast<CSkinnedMesh*>(Mesh);

			skinnedMesh->transferOnlyJointsHintsToMesh( JointChildSceneNodes );

			skinnedMesh->animateMesh(frame, 1.0f);

			skinnedMesh->recoverJointsFromMesh( JointChildSceneNodes);


			if (Transiting != 0.f)
			{

				if (PretransitingSave.size()<JointChildSceneNodes.size())
				{
					for(u32 n=PretransitingSave.size(); n<JointChildSceneNodes.size(); ++n)
						PretransitingSave.push_back(core::matrix4());
				}

				for (u32 n=0; n<JointChildSceneNodes.size(); ++n)
				{


					JointChildSceneNodes[n]->setPosition(
							core::lerp(
								PretransitingSave[n].getTranslation(),
								JointChildSceneNodes[n]->getPosition(),
								TransitingBlend));


					const core::quaternion RotationStart(PretransitingSave[n].getRotationDegrees()*core::DEGTORAD);
					const core::quaternion RotationEnd(JointChildSceneNodes[n]->getRotation()*core::DEGTORAD);

					core::quaternion QRotation;
					QRotation.slerp(RotationStart, RotationEnd, TransitingBlend);

					core::vector3df tmpVector;
					QRotation.toEuler(tmpVector);
					tmpVector*=core::RADTODEG;
					JointChildSceneNodes[n]->setRotation( tmpVector );


				}
			}

			if (CalculateAbsolutePositions)
			{

				for (u32 n=0;n<JointChildSceneNodes.size();++n)
				{
					if (JointChildSceneNodes[n]->getParent()==this)
					{
						JointChildSceneNodes[n]->updateAbsolutePositionOfAllChildren();
					}
				}
			}
		}
	}
}
