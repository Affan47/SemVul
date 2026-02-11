loadGraphicResources (void)
{
    const float screenScale = System::getInstance ().getScreenScaleFactor ();
#if defined (IS_GP2X_HOST)
    const float originalScale = screenScale;
#else
    const float originalScale = 1.0f;
#endif

    m_Background.reset (
            Surface::fromFile (File::getGraphicsFilePath ("menuBackground.png")));
    {
        std::auto_ptr<Surface> podium (
                Surface::fromFile (File::getGraphicsFilePath ("congratulationsPodium.png")));
        podium->blit (m_Background->getWidth () / 2 - podium->getWidth () / 2,
                      m_Background->getHeight () - podium->getHeight (),
                      m_Background->toSDLSurface ());

        std::auto_ptr<Surface> player (
                Surface::fromFile (File::getGraphicsFilePath (getPlayerName () + ".png")));
        player->blit (m_Background->getWidth () / 2 - player->getWidth () / 2,
                      static_cast<uint16_t> (k_PlayerVerticalPosition *
                                             originalScale) -
                      player->getHeight (),
                      m_Background->toSDLSurface ());

        std::auto_ptr<Surface> congratulations (
                Surface::fromFile (File::getGraphicsFilePath ("congratulations.png")));
        congratulations->blit (m_Background->getWidth () / 2 -
                              congratulations->getWidth () / 2, 0,
                              m_Background->toSDLSurface ());
    }
    m_Background->resize (screenScale);
}
