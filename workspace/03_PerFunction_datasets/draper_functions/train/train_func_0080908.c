checkInfeasibility(const OsiBranchingInformation * info) const
{

    if ((branchingStrategy_&8) != 0)
        return 0.0;
    int way;
    double saveInfeasibility = infeasibility_;
    short int saveWhichWay = whichWay_;
    double saveXyBranchValue = xyBranchValue_;
    short saveChosen = chosen_;
    double value = infeasibility(info, way);
    infeasibility_ = saveInfeasibility;
    whichWay_ = saveWhichWay;
    xyBranchValue_ = saveXyBranchValue;
    chosen_ = saveChosen;
    return value;
}
