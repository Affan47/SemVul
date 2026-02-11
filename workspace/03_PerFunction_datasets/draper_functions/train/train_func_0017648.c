setCurrentNameAndNum(string _matrixName, int _matrixNum,
                                          int alignResidueType,int alignType)
{

    checkResidueAndAlignType(alignResidueType, alignType);

    string residue;
    string align;
    if((alignResidueType == Protein) && (alignType == Pairwise))
    {
        residue = "Protein"; align = "Pairwise";
        pwMatrixNum = _matrixNum;
        pwMatrixName = new string(_matrixName);
    }
    else if((alignResidueType == Protein) && (alignType == MultipleAlign))
    {
        residue = "Protein"; align = "MultipleAlign";
        matrixNum = _matrixNum;
        matrixName = new string(_matrixName);
    }
    else if((alignResidueType == DNA) && (alignType == Pairwise))
    {
        residue = "DNA"; align = "Pairwise";
        pwDNAMatrixNum = _matrixNum;
        pwDNAMatrixName = new string(_matrixName);
    }
    else if((alignResidueType == DNA) && (alignType == MultipleAlign))
    {
        residue = "DNA"; align = "MultipleAlign";
        DNAMatrixNum = _matrixNum;
        DNAMatrixName = new string(_matrixName);

    }

    #if DEBUGFULL
        if(logObject && DEBUGLOG)
        {
            ostringstream outs;
            outs << "The matrix/matrix series has been changed for "
                 << "(" << residue << " AND " << align << ")."
                 << " New value: " << _matrixName << "\n\n";
            logObject->logMsg(outs.str());
        }
    #endif
}
