setInSceneGraph(bool inGraph)
    {
        if (inGraph != mIsInSceneGraph)
        {
            mIsInSceneGraph = inGraph;

            ChildNodeMap::iterator child;
            for (child = mChildren.begin(); child != mChildren.end(); ++child)
            {
                SceneNode* sceneChild = static_cast<SceneNode*>(child->second);
                sceneChild->setInSceneGraph(inGraph);
            }
        }
    }
