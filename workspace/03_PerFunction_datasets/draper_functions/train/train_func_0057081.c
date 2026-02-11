loadGraphicResources (void)
{
    const float screenScale = System::getInstance ().getScreenScaleFactor ();
    m_Background.reset (
            Surface::fromFile (File::getGraphicsFilePath ("menuBackground.png")));
    {
        std::ostringstream fileName;
        fileName << "Tournament";
        fileName << m_NumPlayers;
        fileName << "p.png";
        std::auto_ptr<Surface> grid (
                Surface::fromFile (File::getGraphicsFilePath (fileName.str ())));
        grid->blit (m_Background->getWidth () / 2 - grid->getWidth () / 2,
                    m_Background->getHeight () / 2 - grid->getHeight () / 2,
                    m_Background->toSDLSurface ());
    }
    m_Background->resize (screenScale);

    m_Faces.reset (
            Surface::fromFile (File::getGraphicsFilePath ("faces.png")));
    m_Faces->resize (screenScale);
}
