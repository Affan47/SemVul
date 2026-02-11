fillRejectionReasons()
{
    if (rejections_.size() == 0)
    {
        rejections_.resize(DummyEnd) ;
        rejections_[NoneAccepted] = "Cut was accepted";
        rejections_[SmallViolation] = "Violation of the cut is too small ";
        rejections_[SmallCoefficient] = "There is a small coefficient we can not get rid off.";
        rejections_[BigDynamic] = "Dynamic of coefficinet is too important. ";
        rejections_[DenseCut] = "Cut is too dense.";
        rejections_[EmptyCut] = "Cleaned cut is empty";
    }
}
