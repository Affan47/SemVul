setStringValue(const OFString &stringValue)
{
    OFCondition result = EC_IllegalCall;
    if (TreeNode != NULL)
    {
        switch (TreeNode->getValueType())
        {
            case VT_Text:
                result = OFstatic_cast(DSRTextTreeNode *, TreeNode)->setValue(stringValue);
                break;
            case VT_DateTime:
                result = OFstatic_cast(DSRDateTimeTreeNode *, TreeNode)->setValue(stringValue);
                break;
            case VT_Date:
                result = OFstatic_cast(DSRDateTreeNode *, TreeNode)->setValue(stringValue);
                break;
            case VT_Time:
                result = OFstatic_cast(DSRTimeTreeNode *, TreeNode)->setValue(stringValue);
                break;
            case VT_UIDRef:
                result = OFstatic_cast(DSRUIDRefTreeNode *, TreeNode)->setValue(stringValue);
                break;
            case VT_PName:
                result = OFstatic_cast(DSRPNameTreeNode *, TreeNode)->setValue(stringValue);
                break;
            default:
                break;
        }
    }
    return result;
}
