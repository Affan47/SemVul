ConvertRootNode()
	{
		out->mRootNode = new aiNode();
		out->mRootNode->mName.Set("RootNode");


		ConvertNodes(0L, *out->mRootNode);
	}
