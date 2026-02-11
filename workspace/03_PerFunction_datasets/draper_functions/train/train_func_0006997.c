updateDimensions()
{

    int width = (mGroupCount >= mSceneGamesPerLine) ? mSceneGamesPerLine : (mGroupCount % mSceneGamesPerLine);
    int height = (int)(mGroupCount / (mSceneGamesPerLine + 1)) + 1;

    setSceneRect(0, 0, mpGrafx->m_View_Size_Width * width,
                       mpGrafx->m_View_Size_Height * height);

    for(int i = 0; i < mGroupCount; i++)
    {
        int left = mpGrafx->m_View_Size_Width * (i % mSceneGamesPerLine);
        int top = mpGrafx->m_View_Size_Height * ((int)(i / mSceneGamesPerLine));

        maGroupList[i]->setPos(left, top);
        maGroupList[i]->refreshPosition();
    }
}
