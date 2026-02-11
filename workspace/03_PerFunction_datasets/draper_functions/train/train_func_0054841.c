getPath(int index, AIPlanner_PieceInfo_Sequence * pseq)
{
    if ((mPathList == 0) || (index >= (int)mPathList->size()))
    {
        return false;
    }

    PathNode *node  = (*mPathList)[index];
    while (node != 0)
    {
        KBlocksPiece piece = node->getContent();
        pseq->push_back(piece);
        node = node->getParent();
    }

    return true;
}
