AddRule(ASTrule* rule)
{
    bool isShapeItem = rule->mNameIndex == -1;

    if (isShapeItem)
        rule->mNameIndex = mCurrentShape;
    else
        mCurrentShape = -1;

    if (rule->mNameIndex == -1) {
        CfdgError::Error(rule->mLocation, "Shape rules/paths must follow a shape declaration");
        return;
    }

    int type = m_CFDG->getShapeType(rule->mNameIndex);
    if ((rule->isPath &&  type == CFDGImpl::ruleType) ||
        (!rule->isPath && type == CFDGImpl::pathType))
        CfdgError::Error(rule->mLocation, "Cannot mix rules and shapes with the same name.");
    if (rule->isPath && type != CFDGImpl::newShape)
        CfdgError::Error(rule->mLocation, "A given path can only be defined once");

    bool matchesShape = m_CFDG->addRule(rule);

    if (!isShapeItem && matchesShape)
        CfdgError::Error(rule->mLocation, "Rule/path name matches existing shape name");
}
