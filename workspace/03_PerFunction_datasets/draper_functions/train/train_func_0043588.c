animateMesh(f32 frame, f32 blend)
{
	if ( !HasAnimation  || LastAnimatedFrame==frame)
		return;

	LastAnimatedFrame=frame;

	if (blend<=0.f)
		return;

	for (u32 i=0; i<AllJoints.size(); ++i)
	{

		SJoint *joint = AllJoints[i];

		const core::vector3df oldPosition = joint->Animatedposition;
		const core::vector3df oldScale = joint->Animatedscale;
		const core::quaternion oldRotation = joint->Animatedrotation;

		core::vector3df position = oldPosition;
		core::vector3df scale = oldScale;
		core::quaternion rotation = oldRotation;

		getFrameData(frame, joint,
				position, joint->positionHint,
				scale, joint->scaleHint,
				rotation, joint->rotationHint);

		if (blend==1.0f)
		{

			joint->Animatedposition = position;
			joint->Animatedscale = scale;
			joint->Animatedrotation = rotation;
		}
		else
		{

			joint->Animatedposition = core::lerp(oldPosition, position, blend);
			joint->Animatedscale = core::lerp(oldScale, scale, blend);
			joint->Animatedrotation.slerp(oldRotation, rotation, blend);
		}
	}


	buildAll_LocalAnimatedMatrices();


	updateBoundingBox();
}
