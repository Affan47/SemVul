OnRegisterSceneNode()
	{
		if (!IsVisible || !SceneManager->getActiveCamera())
			return;

		preRenderLODCalculations();
		preRenderIndicesCalculations();
		ISceneNode::OnRegisterSceneNode();
		ForceRecalculation = false;
	}
