test()
{
    cout << "RUNNING TEST\n";
    AlignmentOutput alignOutput;
    string path;
    utilityObject->getPath(userParameters->getSeqName(), &path);

    if(!alignOutput.openAlignmentOutput(path))
    {
        cerr << "could not open the file\n";
        return;
    }

    vector<int> selected;
    int nSeqs = alignmentObj.getNumSeqs();
    selected.resize(nSeqs + 1, 0);
    selected[9] = 1;
    selected[10] = 1;

    alignmentObj.removeGapOnlyColsFromSelectedSeqs(&selected);
    alignOutput.createAlignmentOutput(&alignmentObj, 1, nSeqs);
}
