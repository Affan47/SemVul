dataHandler(const char *data, int nLen)
{
    switch(stateStack[nStackDepth])
    {
        case STATE_TOP:                 return OGRERR_NONE; break;
        case STATE_DEFAULT:             return OGRERR_NONE; break;
        case STATE_FEATURE:             return OGRERR_NONE; break;
        case STATE_PROPERTY:            return dataHandlerAttribute(data, nLen); break;
        case STATE_GEOMETRY:            return dataHandlerGeometry(data, nLen); break;
        case STATE_IGNORED_FEATURE:     return OGRERR_NONE; break;
        case STATE_BOUNDED_BY:          return OGRERR_NONE; break;
        case STATE_CITYGML_ATTRIBUTE:   return dataHandlerAttribute(data, nLen); break;
        default:                        return OGRERR_NONE; break;
    }
}
