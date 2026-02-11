replaceParametersReferences(MergeParameterList& mergedParams, ParameterOperandMap& paramsRefMap)
{
    for (unsigned int i=0; i < mergedParams.size(); ++i)
    {
        MergeParameter& curMergeParameter = mergedParams[i];
        int paramBitMaskOffset = 0;

        for (unsigned int j=0; j < curMergeParameter.getSourceParameterCount(); ++j)
        {
            ParameterPtr      curSrcParam  = curMergeParameter.getSourceParameter(j);
            ParameterOperandMap::iterator itParamRefs = paramsRefMap.find(curSrcParam.get());


            if (itParamRefs != paramsRefMap.end())
            {
                OperandPtrVector& srcParamRefs = itParamRefs->second;
                ParameterPtr dstParameter;


                if (curMergeParameter.getSourceParameterMask(j) == Operand::OPM_ALL)
                {
                    dstParameter = curMergeParameter.getDestinationParameter(Operand::OPS_INOUT, i);

                    for (unsigned int op=0; op < srcParamRefs.size(); ++op)
                    {
                        Operand*  srcOperandPtr = srcParamRefs[op];
                        int       dstOpMask;

                        if (srcOperandPtr->getMask() == Operand::OPM_ALL)
                        {

                            if (curMergeParameter.getSourceParameterCount() == 1)
                            {
                                dstOpMask = Operand::OPM_ALL;
                            }
                            else
                            {
                                dstOpMask = getParameterMaskByType(curSrcParam->getType()) << paramBitMaskOffset;
                            }
                        }
                        else
                        {
                            dstOpMask = srcOperandPtr->getMask() << paramBitMaskOffset;
                        }


                        *srcOperandPtr = Operand(dstParameter, srcOperandPtr->getSemantic(), dstOpMask);
                    }
                }
            }


            paramBitMaskOffset += getParameterFloatCount(curSrcParam->getType());
        }
    }
}
