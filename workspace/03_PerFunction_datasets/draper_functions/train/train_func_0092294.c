backgroundColoring()
{
    if(backGroundColors)
    {
        backGroundColors = false;
    }
    else
    {
        backGroundColors = true;
    }

    alignmentViewer->setBackGroundColoring(backGroundColors);
    profile2Viewer->setBackGroundColoring(backGroundColors);
}
