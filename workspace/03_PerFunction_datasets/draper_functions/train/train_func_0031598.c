ajResidueExistsBin(ajint base)
{
    if(!aj_residue_I)
	residueInit();

    if(ajStrGetLen(aj_residue_iubS[base].code))
        return ajTrue;

    return ajFalse;
}
