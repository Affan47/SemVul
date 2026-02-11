operationTypeToString(RenderOperation::OperationType val)
    {
        switch (val)
        {
        case RenderOperation::OT_POINT_LIST:
            return "point_list";
            break;
        case RenderOperation::OT_LINE_LIST:
            return "line_list";
            break;
        case RenderOperation::OT_LINE_STRIP:
            return "line_strip";
            break;
        case RenderOperation::OT_TRIANGLE_STRIP:
            return "triangle_strip";
            break;
        case RenderOperation::OT_TRIANGLE_FAN:
            return "triangle_fan";
            break;
        case RenderOperation::OT_TRIANGLE_LIST:
        default:
            return "triangle_list";
            break;
        }
    }
