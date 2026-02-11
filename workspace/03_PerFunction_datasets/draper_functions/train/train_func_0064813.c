ParseLV2AnimationBlock(ASE::BaseNode& mesh)
{
	AI_ASE_PARSER_INIT();

	ASE::Animation* anim = &mesh.mAnim;
	while (true)
	{
		if ('*' == *filePtr)
		{
			++filePtr;
			if (TokenMatch(filePtr,"NODE_NAME" ,9))
			{
				std::string temp;
				if(!ParseString(temp,"*NODE_NAME"))
					SkipToNextToken();


				if (std::string::npos != temp.find(".Target"))
				{
					if  ((mesh.mType != BaseNode::Camera || ((ASE::Camera&)mesh).mCameraType != ASE::Camera::TARGET)  &&
						( mesh.mType != BaseNode::Light  || ((ASE::Light&)mesh).mLightType   != ASE::Light::TARGET))
					{

						DefaultLogger::get()->error("ASE: Found target animation channel "
							"but the node is neither a camera nor a spot light");
						anim = NULL;
					}
					else anim = &mesh.mTargetAnim;
				}
				continue;
			}


			if (TokenMatch(filePtr,"CONTROL_POS_TRACK"  ,17)  ||
				TokenMatch(filePtr,"CONTROL_POS_BEZIER" ,18)  ||
				TokenMatch(filePtr,"CONTROL_POS_TCB"    ,15))
			{
				if (!anim)SkipSection();
				else ParseLV3PosAnimationBlock(*anim);
				continue;
			}

			if (TokenMatch(filePtr,"CONTROL_SCALE_TRACK"  ,19) ||
				TokenMatch(filePtr,"CONTROL_SCALE_BEZIER" ,20) ||
				TokenMatch(filePtr,"CONTROL_SCALE_TCB"    ,17))
			{
				if (!anim || anim == &mesh.mTargetAnim)
				{

					DefaultLogger::get()->error("ASE: Ignoring scaling channel in target animation");
					SkipSection();
				}
				else ParseLV3ScaleAnimationBlock(*anim);
				continue;
			}

			if (TokenMatch(filePtr,"CONTROL_ROT_TRACK"  ,17) ||
				TokenMatch(filePtr,"CONTROL_ROT_BEZIER" ,18) ||
				TokenMatch(filePtr,"CONTROL_ROT_TCB"    ,15))
			{
				if (!anim || anim == &mesh.mTargetAnim)
				{

					DefaultLogger::get()->error("ASE: Ignoring rotation channel in target animation");
					SkipSection();
				}
				else ParseLV3RotAnimationBlock(*anim);
				continue;
			}
		}
		AI_ASE_HANDLE_SECTION("2","TM_ANIMATION");
	}
}
