initialiseSample()
{
    using namespace CEGUI;


    WindowManager& winMgr = WindowManager::getSingleton();


    SchemeManager::getSingleton().create("TaharezLook.scheme");
    System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    FontManager::getSingleton().create("DejaVuSans-10.font");


    ImagesetManager::getSingleton().createFromImageFile("BackgroundImage", "GPN-2000-001437.tga");


    Window* background = winMgr.createWindow("TaharezLook/StaticImage", "root_wnd");

    background->setPosition(UVector2(cegui_reldim(0), cegui_reldim( 0)));
    background->setSize(UVector2(cegui_reldim(1), cegui_reldim( 1)));

    background->setProperty("FrameEnabled", "false");
    background->setProperty("BackgroundEnabled", "false");

    background->setProperty("Image", "set:BackgroundImage image:full_image");

    System::getSingleton().setGUISheet(background);


    createDemoWindows();
    initDemoEventWiring();


    return true;
}
