nextUp(DcmStack &stack)
{
    DcmObject *oldContainer = stack.pop();
    if (oldContainer->isLeaf())
        return EC_IllegalCall;
    else if (!stack.empty())
    {
        DcmObject *container = stack.top();
        DcmObject *result = container->nextInContainer(oldContainer);
        if (result)
        {
            stack.push(result);
            return EC_Normal;
        }
        else
            return nextUp(stack);
    }
    return EC_TagNotFound;
}
