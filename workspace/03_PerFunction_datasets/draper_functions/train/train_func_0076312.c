checkContentRelationship(const E_ValueType sourceValueType,
                                                                      const E_RelationshipType relationshipType,
                                                                      const E_ValueType targetValueType,
                                                                      const OFBool byReference) const
{

    OFBool result = OFFalse;

    if ((relationshipType == RT_contains) && !byReference && (sourceValueType == VT_Container))
    {
        result = (targetValueType == VT_Code) || (targetValueType == VT_Num) || (targetValueType == VT_SCoord) ||
                 (targetValueType == VT_Image) || (targetValueType == VT_Container) ||
                 (targetValueType == VT_Text) || (targetValueType == VT_Date);
    }

    else if ((relationshipType == RT_hasObsContext) && !byReference && ((sourceValueType == VT_Container) ||
        (sourceValueType == VT_Text) || (sourceValueType == VT_Code) || (sourceValueType == VT_Num)))
    {
        result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_Num) ||
                 (targetValueType == VT_Date) || (targetValueType == VT_Time) || (targetValueType == VT_PName) ||
                 (targetValueType == VT_UIDRef) || (targetValueType == VT_Composite);
    }

    else if ((relationshipType == RT_hasAcqContext) && !byReference && (sourceValueType == VT_Image))
    {
        result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_Date) ||
                 (targetValueType == VT_Time) || (targetValueType == VT_Num);
    }

    else if ((relationshipType == RT_hasConceptMod) && !byReference &&
        ((sourceValueType == VT_Container) || (sourceValueType == VT_Code) ||
        (sourceValueType == VT_Num) || (sourceValueType == VT_Composite)))
    {
        result = (targetValueType == VT_Text) || (targetValueType == VT_Code);
    }

    else if ((relationshipType == RT_hasProperties) &&
        ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) || (sourceValueType == VT_Num)))
    {

        result = (targetValueType == VT_Container) || (targetValueType == VT_Text) || (targetValueType == VT_Code) ||
                 (targetValueType == VT_Num) || (targetValueType == VT_Date) || (targetValueType == VT_Image) ||
                 (targetValueType == VT_SCoord) || (targetValueType == VT_UIDRef);
    }

    else if ((relationshipType == RT_inferredFrom) && ((sourceValueType == VT_Code) || (sourceValueType == VT_Num)))
    {

        result = (targetValueType == VT_Code) || (targetValueType == VT_Num) || (targetValueType == VT_SCoord) ||
                 (targetValueType == VT_Container) || (targetValueType == VT_Text) ||
                 (targetValueType == VT_Image);
    }

    else if ((relationshipType == RT_selectedFrom) && (sourceValueType == VT_SCoord))
    {

        result = (targetValueType == VT_Image);
    }
    return result;
}
