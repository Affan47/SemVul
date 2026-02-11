setPaperOrientation(QPrinter::Orientation orientation)
{
    (
        orientation == QPrinter::Landscape?m_paperOrientationLandscapeRadioButton
        :m_paperOrientationPortraitRadioButton
    )->setChecked(true);
}
