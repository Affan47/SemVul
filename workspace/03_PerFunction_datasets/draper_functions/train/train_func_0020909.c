free()
{
    if (!d_fontFace)
        return;

    d_cp_map.clear();

    for (size_t i = 0; i < d_glyphImages.size(); i++)
        ImagesetManager::getSingleton().destroy(d_glyphImages [i]->getName());
    d_glyphImages.clear();

    FT_Done_Face(d_fontFace);
    d_fontFace = 0;
    System::getSingleton().getResourceProvider()->unloadRawDataContainer(d_fontData);
}
