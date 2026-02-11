processShape(const Shape& s)
{
    double area = s.area();
    if (!isfinite(area)) {
        requestStop = true;
        system()->error();
        system()->message("A shape got too big.");
        s.releaseParams();
        return;
    }

    if (s.mWorldState.m_time.tbegin > s.mWorldState.m_time.tend) {
        s.releaseParams();
        return;
    }

    if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::ruleType &&
        m_cfdg->shapeHasRules(s.mShapeType))
    {

        if (!mBounds.valid() || (area * mScaleArea >= m_minArea)) {
            m_stats.toDoCount++;
            mUnfinishedShapes.push_back(s);
            push_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end());
        } else {
            s.releaseParams();
        }
    } else if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::pathType) {
        const ASTrule* rule = m_cfdg->findRule(s.mShapeType, 0.0);
        processPrimShape(s, rule);
    } else if (primShape::isPrimShape(s.mShapeType)) {
        processPrimShape(s);
    } else {
        requestStop = true;
        s.releaseParams();
        system()->error();
        system()->message("Shape with no rules encountered: %s.",
            m_cfdg->decodeShapeName(s.mShapeType).c_str());
    }
}
