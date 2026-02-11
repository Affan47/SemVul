addSceneTreeItem( ISceneNode * parent, IGUITreeViewNode* nodeParent)
{
	IGUITreeViewNode* node;
	wchar_t msg[128];

	s32 imageIndex;
	list<ISceneNode*>::ConstIterator it = parent->getChildren().begin();
	for (; it != parent->getChildren().end(); ++it)
	{
		switch ( (*it)->getType () )
		{
			case ESNT_Q3SHADER_SCENE_NODE: imageIndex = 0; break;
			case ESNT_CAMERA: imageIndex = 1; break;
			case ESNT_EMPTY: imageIndex = 2; break;
			case ESNT_MESH: imageIndex = 3; break;
			case ESNT_OCTREE: imageIndex = 3; break;
			case ESNT_ANIMATED_MESH: imageIndex = 4; break;
			case ESNT_SKY_BOX: imageIndex = 5; break;
			case ESNT_BILLBOARD: imageIndex = 6; break;
			case ESNT_PARTICLE_SYSTEM: imageIndex = 7; break;
			case ESNT_TEXT: imageIndex = 8; break;
			default:imageIndex = -1; break;
		}

		if ( imageIndex < 0 )
		{
			swprintf ( msg, 128, L"%hs,%hs",
				Game->Device->getSceneManager ()->getSceneNodeTypeName ( (*it)->getType () ),
				(*it)->getName()
				);
		}
		else
		{
			swprintf ( msg, 128, L"%hs",(*it)->getName() );
		}

		node = nodeParent->addChildBack( msg, 0, imageIndex );


		list<ISceneNodeAnimator*>::ConstIterator ait = (*it)->getAnimators().begin();
		for (; ait != (*it)->getAnimators().end(); ++ait)
		{
			imageIndex = -1;
			swprintf ( msg, 128, L"%hs",
				Game->Device->getSceneManager ()->getAnimatorTypeName ( (*ait)->getType () )
				);

			switch ( (*ait)->getType () )
			{
				case ESNAT_FLY_CIRCLE:
				case ESNAT_FLY_STRAIGHT:
				case ESNAT_FOLLOW_SPLINE:
				case ESNAT_ROTATION:
				case ESNAT_TEXTURE:
				case ESNAT_DELETION:
				case ESNAT_COLLISION_RESPONSE:
				case ESNAT_CAMERA_FPS:
				case ESNAT_CAMERA_MAYA:
				default:
					break;
			}
			node->addChildBack( msg, 0, imageIndex );
		}

		addSceneTreeItem ( *it, node );
	}
}
